#ifndef MARVIN_DOWNLOAD_H
#define MARVIN_DOWNLOAD_H

#include <vector>
#include <string>
#include "types.h"

namespace download {

    memory_block fetch_url(const std::string &url);

}
#endif //MARVIN_DOWNLOAD_H