#include <fstream>
#include <utility>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <boost/log/trivial.hpp>
#include <bitset>

#include "tensorflow/cc/ops/const_op.h"
#include "tensorflow/cc/ops/image_ops.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/core/framework/graph.pb.h"
#include "tensorflow/core/graph/default_device.h"
#include "tensorflow/core/graph/graph_def_builder.h"
#include "tensorflow/core/lib/core/threadpool.h"
#include "tensorflow/core/lib/io/path.h"
#include "tensorflow/core/lib/strings/stringprintf.h"
#include "tensorflow/core/platform/init_main.h"
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/util/command_line_flags.h"


using tensorflow::Flag;
using tensorflow::Tensor;
using tensorflow::Status;
using tensorflow::string;
using tensorflow::int32;

#include "tensorflow.h"

using namespace std;
using namespace boost;

namespace ml {
    namespace images {

        Inception::Inception(std::string graph_file_name, std::string labels_file_name) {
            tensorflow::GraphDef graph_def;
            Status status = ReadBinaryProto(tensorflow::Env::Default(), graph_file_name, &graph_def);
            if (!status.ok()) {
                BOOST_LOG_TRIVIAL(error) << format("unable to load compute graph at %s, %s") % graph_file_name % status.error_message();
            }
            status = tensorflow::NewSession(tensorflow::SessionOptions(), &session);
            if (!status.ok()) {
                BOOST_LOG_TRIVIAL(error) << format("failure creating new session, %s") % status.error_message();
            }
            status = session->Create(graph_def);
            if (!status.ok()) {
                BOOST_LOG_TRIVIAL(error) << format("unable to create session for compute graph at %s, %s") % graph_file_name % status.error_message();
            }
            ifstream file(labels_file_name);
            if (!file) {
                BOOST_LOG_TRIVIAL(error) << format("Labels file %s not found.") % labels_file_name;
            }
            labels.clear();
            string line;
            while (getline(file, line)) {
                labels.push_back(line);
            }
            found_label_count = labels.size();
            const int padding = 16;
            while (labels.size() % padding) {
                labels.emplace_back();
            }
        }

        Inception::~Inception() {
            Status session_close = session->Close();
            if (!session_close.ok()) {
                BOOST_LOG_TRIVIAL(error) << format("could not close session, %s") % session_close.error_message();
            }
        }

        vector<inception_score> Inception::classify(memory_block *block, int width, int height) {
            vector<inception_score> result;

            auto root = tensorflow::Scope::NewRootScope();
            using namespace ::tensorflow::ops;

            tensorflow::StringPiece data(block->memory, block->size);
            Tensor input(tensorflow::DT_STRING, tensorflow::TensorShape());
            (&input)->scalar<string>()() = data.ToString();

            auto reader = Placeholder(root.WithOpName("input"), tensorflow::DataType::DT_STRING);
            const int wanted_channels = 3;
            tensorflow::Output image_reader;

            switch(block->type) {
                case png:
                    image_reader = DecodePng(root.WithOpName("png_reader"), reader, DecodePng::Channels(wanted_channels));
                    break;
                case gif:
                    image_reader = Squeeze(root.WithOpName("squeeze_first_dim"), DecodeGif(root.WithOpName("gif_reader"), reader));
                    break;
                case bmp:
                    image_reader = DecodeBmp(root.WithOpName("bmp_reader"), reader);
                    break;
                case jpg:
                    image_reader = DecodeJpeg(root.WithOpName("jpeg_reader"), reader, DecodeJpeg::Channels(wanted_channels));
                case unkown:
                    BOOST_LOG_TRIVIAL(error) << "could not determine image type to analyze, aborting...";
                    return result;
            }

            auto float_caster = Cast(root.WithOpName("float_caster"), reader, tensorflow::DT_FLOAT);
            auto dims_expander = ExpandDims(root, float_caster, 0);
            auto resized = ResizeBilinear(root, dims_expander, Const(root.WithOpName("size"), {height, width}));

            Div(root.WithOpName("normalized"), Sub(root, resized, {input_mean}), {input_std});

            tensorflow::GraphDef image_graph;
            Status status = root.ToGraphDef(&image_graph);
            if (!status.ok()) {
                BOOST_LOG_TRIVIAL(error) << format("could not create image_graph definition, %s") % status.error_message();
                return result;
            }

            session.reset(tensorflow::NewSession(tensorflow::SessionOptions()));

            status = session->Create(image_graph);
            if (!status.ok()) {
                BOOST_LOG_TRIVIAL(error) << format("could not create image_graph, %s") % status.error_message();
                return result;
            }

            vector<Tensor> outputs;
            vector<pair<string, tensorflow::Tensor>> inputs = { {"input", input}, };
            status = session->Run({inputs}, {"normalized"}, {}, &outputs);
            if (!status.ok()) {
                BOOST_LOG_TRIVIAL(error) << format("failure during analysis, %s") % status.error_message();
                return result;
            }

            string output_name = "top_k";
            TopK(root.WithOpName(output_name), outputs[0], min(5, static_cast<int>(found_label_count)));

            tensorflow::GraphDef label_graph;
            status = root.ToGraphDef(&label_graph);
            if (!status.ok()) {
                BOOST_LOG_TRIVIAL(error) << format("could not create label_graph definition, %s") % status.error_message();
                return result;
            }

            session.reset(tensorflow::NewSession(tensorflow::SessionOptions()));

            status = session->Create(label_graph);
            if (!status.ok()) {
                BOOST_LOG_TRIVIAL(error) << format("could not create label_graph, %s") % status.error_message();
                return result;
            }

            std::vector<Tensor> out_tensors;
            status = session->Run({}, {output_name + ":0", output_name + ":1"}, {}, &out_tensors));

            if (!status.ok()) {
                BOOST_LOG_TRIVIAL(error) << format("could not create execute run, %s") % status.error_message();
                return result;
            }

            tensorflow::TTypes<float>::Flat scores_flat = out_tensors[0].flat<float>();
            tensorflow::TTypes<int32>::Flat indices_flat = out_tensors[1].flat<int32>();

            for (int pos = 0; pos < min(5, static_cast<int>(found_label_count)); ++pos) {
                const int label_index = indices_flat(pos);
                const float score = scores_flat(pos);
                result.push_back(inception_score{labels[label_index], label_index, score});
            }

            return result;
        }

    }
}