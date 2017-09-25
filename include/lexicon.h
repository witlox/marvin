#ifndef MARVIN_LEXICON_H
#define MARVIN_LEXICON_H

#include <string>

namespace lexicon {
    float score(std::wstring word);
    bool contains(std::wstring word);
}

#endif //MARVIN_LEXICON_H
