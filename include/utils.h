#ifndef MARVIN_UTILS_H
#define MARVIN_UTILS_H

#include <ctime>
#include <string>

namespace utils {
    time_t seconds_from_epoch(const std::string &s);
    std::vector<std::wstring> intersection(std::vector<std::wstring> &v1, std::vector<std::wstring> &v2);
}

#endif //MARVIN_UTILS_H
