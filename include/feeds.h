#ifndef MARVIN_FEED_PARSER_H
#define MARVIN_FEED_PARSER_H

#include <string>
#include "types.h"

namespace feeds {

    feed_t parse(std::string url);

}

#endif //MARVIN_FEED_PARSER_H
