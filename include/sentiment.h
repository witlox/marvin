#ifndef MARVIN_SENTIMENT_H
#define MARVIN_SENTIMENT_H

#include "utils.h"

namespace sentiment {

    typedef std::map<std::wstring, float> Influencer;

    namespace text {

        typedef std::map<std::wstring, std::wstring> WordsPlusPunctuation;

        /**
        * Map the words in a text to all possible punctuations as a map
        * Key is punctuated word, value is original word
        * ex. {
        *       'cat.' , 'cat'
        *       '.cat' , 'cat'
        *     }
        * @param text original text
        * @return all possible puntuations
        */
        WordsPlusPunctuation words_plus_punctuation(std::wstring text);

        /**
        * Removes leading and trailing punctuation
        * Leaves contractions and most emoticons
        * Does not preserve punc-plus-letter emoticons (e.g. :D)
        * @param text original text as string
        * @return Array of words
        */
        std::vector<std::wstring> words_and_emoticons(std::wstring text);
    };

    namespace helpers {

        /**
          * Determine if input contains negation words
          * @param words list of words
          * @param include_nt include n't
          * @return negated or not
          */
        bool negated(std::vector<std::wstring> words, bool include_nt = true);

        /**
          * Normalize the score to be between -1 and 1 using an alpha that
          * approximates the max expected value
          * @param score original
          * @param alpha approximator
          * @return normalized score
          */
        double normalize(float score, int alpha = 15);

        /**
          * Check whether just some words in the input are ALL CAPS
          * @param words list of words
          * @return all capitals yes or no
          */
        bool all_caps_differential(std::vector<std::wstring> words);

        /**
          * Check if the preceding words increase, decrease, or negate/nullify the valence
          * @param word the word to analyse
          * @param valence original valence
          * @param cap_diff capital differential
          * @return scalar
          */
        double determine_scalar(const std::wstring &word, double valence, bool cap_diff);
    }

    namespace analyzer {

        struct sentiment_score {
            double positive;
            double negative;
            double neutral;
            double compound;
        };

        /**
        * Return a float for sentiment strength based on the input text.
        * Positive values are positive valence, negative value are negative valence.
        * @param text: string of text to analyse
        * @return struct of negative neutral positive and compound sentiment
        */
        sentiment_score polarity(const std::wstring &text);
    }
}
#endif //MARVIN_SENTIMENT_H
