#ifndef MARVIN_TYPES_H
#define MARVIN_TYPES_H

#include <ctime>

struct media_t {
    std::string media;
    std::string type;
};

struct item_t {
    std::string title;
    std::string title_type;
    std::string link;
    std::string description;
    std::string description_type;
    std::string author;
    std::string author_email;
    std::string pubDate;
    std::string guid;
    std::vector<media_t> media;
};

struct feed_t {
    std::string encoding;
    std::string title;
    std::string title_type;
    std::string description;
    std::string link;
    std::string language;
    std::string pubDate;
    std::vector<item_t> items;
};

#endif //MARVIN_TYPES_H
