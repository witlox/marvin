#include <boost/date_time.hpp>
#include <netinet/in.h>

#include "utils.h"

using namespace std;

namespace bt = boost::posix_time;

namespace utils {

    const std::locale formats[] = {
            std::locale(std::locale::classic(), new bt::time_input_facet("%Y-%m-%d %H:%M:%S")),
            std::locale(std::locale::classic(), new bt::time_input_facet("%Y/%m/%d %H:%M:%S")),
            std::locale(std::locale::classic(), new bt::time_input_facet("%d.%m.%Y %H:%M:%S")),
            std::locale(std::locale::classic(), new bt::time_input_facet("%Y-%m-%d")),
            std::locale(std::locale::classic(), new bt::time_input_facet("%a, %d %m %Y %H:%M:%S z")),
    };

    time_t pt_to_time_t(const bt::ptime &pt) {
        bt::ptime timet_start(boost::gregorian::date(1970, 1, 1));
        bt::time_duration diff = pt - timet_start;
        return diff.ticks() / bt::time_duration::rep_type::ticks_per_second;
    }

    time_t seconds_from_epoch(const string &s) {
        bt::ptime pt;
        for (const auto &format : formats) {
            istringstream is(s);
            is.imbue(format);
            is >> pt;
            if (pt != bt::ptime()) break;
        }
        return pt_to_time_t(pt);
    }

    vector<wstring> intersection(vector<wstring> &v1, vector<wstring> &v2) {
        vector<wstring> intersect;
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(intersect));
        return intersect;
    }

    bool determine_image_dimensions(char *image, size_t size, int *width, int *height){
        // In all formats, the file is at least 24 bytes big, so we'll read that always
        unsigned char buf[24];
        memcpy(buf, image, 24);

        // For JPEGs, we need to read the first 12 bytes of each chunk.
        // We'll read those 12 bytes at buf+2...buf+14, i.e. overwriting the existing buf.
        if (buf[0]==0xFF && buf[1]==0xD8 && buf[2]==0xFF && buf[3]==0xE0 && buf[6]=='J' && buf[7]=='F' && buf[8]=='I' && buf[9]=='F') {
            long pos=2;
            while (buf[2]==0xFF) {
                if (buf[3]==0xC0 || buf[3]==0xC1 || buf[3]==0xC2 || buf[3]==0xC3 || buf[3]==0xC9 || buf[3]==0xCA || buf[3]==0xCB) {
                    break;
                }
                pos += 2+(buf[4]<<8)+buf[5];
                if (pos+12>size) break;
                memcpy(buf+2, image + pos, 12);
            }
        }

        // JPEG: (first two bytes of buf are first two bytes of the jpeg file; rest of buf is the DCT frame
        if (buf[0]==0xFF && buf[1]==0xD8 && buf[2]==0xFF) {
            *height = (buf[7]<<8) + buf[8];
            *width = (buf[9]<<8) + buf[10];
            return true;
        }

        // GIF: first three bytes say "GIF", next three give version number. Then dimensions
        if (buf[0]=='G' && buf[1]=='I' && buf[2]=='F') {
            *width = buf[6] + (buf[7]<<8);
            *height = buf[8] + (buf[9]<<8);
            return true;
        }

        // PNG: the first frame is by definition an IHDR frame, which gives dimensions
        if (buf[0]==0x89 && buf[1]=='P' && buf[2]=='N' && buf[3]=='G' && buf[4]==0x0D && buf[5]==0x0A && buf[6]==0x1A && buf[7]==0x0A && buf[12]=='I' && buf[13]=='H' && buf[14]=='D' && buf[15]=='R') {
            *width = (buf[16]<<24) + (buf[17]<<16) + (buf[18]<<8) + (buf[19]<<0);
            *height = (buf[20]<<24) + (buf[21]<<16) + (buf[22]<<8) + (buf[23]<<0);
            return true;
        }

        // BMP: offset after bit 18
        if (buf[0]=='B' && buf[1]=='M') {
            *width = (buf[18]<<24) + (buf[19]<<16) + (buf[20]<<8) + (buf[21]<<0);
            *height = (buf[22]<<24) + (buf[23]<<16) + (buf[24]<<8) + (buf[25]<<0);
            return true;
        }

        return false;
    }
}
