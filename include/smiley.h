#ifndef MARVIN_SMILEY_H
#define MARVIN_SMILEY_H

#include <string>

namespace smiley {
    bool is_positive(const std::wstring &word);
    bool is_negative(const std::wstring &word);
    bool is_neutral(const std::wstring &word);
    bool is_smiley(const std::wstring &word);
}

#endif //MARVIN_SMILEY_H
