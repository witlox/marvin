#ifndef MARVIN_TYPES_H
#define MARVIN_TYPES_H

#include <ctime>

struct media_t {
    std::wstring media;
    std::wstring type;
};

struct item_t {
    std::wstring title;
    std::string title_type;
    std::wstring link;
    std::wstring description;
    std::string description_type;
    std::wstring author;
    std::wstring author_email;
    std::wstring pubDate;
    std::wstring guid;
    std::vector<media_t> media;
};

struct feed_t {
    std::string encoding;
    std::wstring title;
    std::string title_type;
    std::wstring description;
    std::wstring link;
    std::wstring language;
    std::wstring pubDate;
    std::vector<item_t> items;
};

typedef enum {
    png,
    jpg,
    gif,
    bmp,
    unkown
} memory_type;

struct memory_block {
    char *memory;
    size_t size;
    memory_type type;
};

#endif //MARVIN_TYPES_H
