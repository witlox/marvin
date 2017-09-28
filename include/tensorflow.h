#ifndef MARVIN_TENSORFLOW_H
#define MARVIN_TENSORFLOW_H

#include <tensorflow/c/c_api.h>
#include <tensorflow/core/public/session.h>

#include "types.h"

namespace ml {
    namespace images {
        struct inception_score {
            std::string name;
            int index;
            double score;
        };
        class Inception {
        public:
            Inception(std::string graph_file_name, std::string labels_file_name);
            std::vector<inception_score> classify(memory_block *block, int width, int height);
            ~Inception();
        private:
            std::unique_ptr<tensorflow::Session> session;
            std::vector<std::string> labels;
            size_t found_label_count;
            float input_mean = 0;
            float input_std = 255;
        };
    }
}

#endif //MARVIN_TENSORFLOW_H
