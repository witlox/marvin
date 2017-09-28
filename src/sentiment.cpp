#include <regex>

#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <lexicon.h>

#include "sentiment.h"
#include "emoji.h"

using namespace std;
using namespace boost;

namespace sentiment {

    double nscalar = -0.74;

    namespace text {

        static const wstring punctuations[] = {L".", L"!", L"?", L",", L";", L":", L"-", L"'", L"\"", L"!!", L"!!!", L"??", L"???", L"?!?", L"!?!", L"?!?!", L"!?!?"};

        bool is_punct(wchar_t character) {
            return ispunct(character, locale("C"));
        }

        WordsPlusPunctuation words_plus_punctuation(wstring text) {
            // get all of our words
            text.erase(remove_if(text.begin(), text.end(), is_punct), text.end());
            vector<wstring> words;
            split(words, text, is_any_of(L" "));
            // build all possible punctuations
            WordsPlusPunctuation result;
            for (const wstring &word: words) {
                wstring filtered = emoji::get_text(word);
                for (const wstring &punctuation: punctuations) {
                    result[punctuation + filtered] = filtered;
                    result[filtered + punctuation] = filtered;
                }
            }
            return result;
        }

        vector<wstring> words_and_emoticons(wstring text) {
            WordsPlusPunctuation wpp = words_plus_punctuation(text);
            vector<wstring> words;
            split(words, text, is_any_of(L" "));
            // build our result list
            vector<wstring> result;
            for (const wstring &word: words) {
                if (word.length() > 1) {
                    if (wpp.find(word) == wpp.end()) {
                        result.push_back(word);
                    } else {
                        result.push_back(wpp[word]);
                    }
                }
            }
            return result;
        }
    }
    namespace helpers {

        // (empirically derived mean sentiment intensity rating intensity_increase for booster words)
        double booster_increase = 0.293;
        double booster_decrease = -0.293;

        // (empirically derived mean sentiment intensity rating intensity_increase for using ALLCAPs to emphasize a word)
        double intensity_increase = 0.733;

        // negation words
        const std::wstring negate[] = {
                L"aint", L"arent", L"cannot", L"cant", L"couldnt", L"darent", L"didnt", L"doesnt", L"ain't", L"aren't", L"can't",
                L"couldn't", L"daren't", L"didn't", L"doesn't", L"dont", L"hadnt", L"hasnt", L"havent", L"isnt", L"mightnt", L"mustnt", L"neither",
                L"don't", L"hadn't", L"hasn't", L"haven't", L"isn't", L"mightn't", L"mustn't", L"neednt", L"needn't", L"never", L"none", L"nope",
                L"nor", L"not", L"nothing", L"nowhere", L"oughtnt", L"shant", L"shouldnt", L"uhuh", L"wasnt", L"werent", L"oughtn't", L"shan't",
                L"shouldn't", L"uh-uh", L"wasn't", L"weren't", L"without", L"wont", L"wouldnt", L"won't", L"wouldn't", L"rarely", L"seldom",
                L"despite"
        };

        // booster/dampener 'intensifiers' or 'degree adverbs' http://en.wiktionary.org/wiki/Category:English_degree_adverbs
        Influencer booster_dictionary = {
                {L"absolutely", booster_increase},
                {L"amazingly", booster_increase},
                {L"awfully", booster_increase},
                {L"completely", booster_increase},
                {L"considerably", booster_increase},
                {L"decidedly", booster_increase},
                {L"deeply", booster_increase},
                {L"effing", booster_increase},
                {L"enormously", booster_increase},
                {L"entirely", booster_increase},
                {L"especially", booster_increase},
                {L"exceptionally", booster_increase},
                {L"extremely", booster_increase},
                {L"fabulously", booster_increase},
                {L"flipping", booster_increase},
                {L"flippin", booster_increase},
                {L"fricking", booster_increase},
                {L"frickin", booster_increase},
                {L"frigging", booster_increase},
                {L"friggin", booster_increase},
                {L"fully", booster_increase},
                {L"fucking", booster_increase},
                {L"greatly", booster_increase},
                {L"hella", booster_increase},
                {L"highly", booster_increase},
                {L"hugely", booster_increase},
                {L"incredibly", booster_increase},
                {L"intensely", booster_increase},
                {L"majorly", booster_increase},
                {L"more", booster_increase},
                {L"most", booster_increase},
                {L"particularly", booster_increase},
                {L"purely", booster_increase},
                {L"quite", booster_increase},
                {L"really", booster_increase},
                {L"remarkably", booster_increase},
                {L"so", booster_increase},
                {L"substantially", booster_increase},
                {L"thoroughly", booster_increase},
                {L"totally", booster_increase},
                {L"tremendously", booster_increase},
                {L"uber", booster_increase},
                {L"unbelievably", booster_increase},
                {L"unusually", booster_increase},
                {L"utterly", booster_increase},
                {L"very", booster_increase},
                {L"almost", booster_decrease},
                {L"barely", booster_decrease},
                {L"hardly", booster_decrease},
                {L"just enough", booster_decrease},
                {L"kind of", booster_decrease},
                {L"kinda", booster_decrease},
                {L"kindof", booster_decrease},
                {L"kind-of", booster_decrease},
                {L"less", booster_decrease},
                {L"little", booster_decrease},
                {L"marginally", booster_decrease},
                {L"occasionally", booster_decrease},
                {L"partly", booster_decrease},
                {L"scarcely", booster_decrease},
                {L"slightly", booster_decrease},
                {L"somewhat", booster_decrease},
                {L"sort of", booster_decrease},
                {L"sorta", booster_decrease},
                {L"sortof", booster_decrease},
                {L"sort-of", booster_decrease}
        };

        bool negated(vector<wstring> words, bool include_nt) {
            if (words.empty()) {
                return false;
            }
            vector<wstring> v(begin(negate), end(negate));
            if (!utils::intersection(words, v).empty()) {
                return true;
            }
            if (include_nt) {
                for (const wstring &word: words) {
                    if (word.find(L"n't") !=  string::npos) {
                        return true;
                    }
                }
            }
            for (int i = 0; i < words.size(); i++) {
                wstring word = words[i];
                if (iequals(word, L"least")) {
                    if (i > 0) {
                        if (iequals(words[i-1], L"at")) {
                            return true;
                        }
                    }
                }
            }
            return false;
        }

        double normalize(double score, int alpha = 15) {
            double norm_score = score / sqrt((score * score) + alpha);
            if (norm_score < -1.0) {
                return -1.0;
            }
            if (norm_score > 1.0) {
                return 1.0;
            }
            return norm_score;
        }

        bool all_caps_differential(vector<wstring> words) {
            int caps_count = 0;
            for (auto word: words) {
                if (all_of(word.begin(), word.end(), is_upper())) {
                    caps_count++;
                }
            }
            return words.size() - caps_count > 0 && words.size() - caps_count < words.size();
        }

        double determine_scalar(const wstring &word, double valence, bool cap_diff) {
            wstring word_lower = to_lower_copy(word);
            if (booster_dictionary.find(word_lower) != booster_dictionary.end()) {
                double scalar = booster_dictionary[word_lower];
                if (valence < 0) {
                    scalar *= -1;
                }
                if (all_of(word.begin(), word.end(), &::isupper) && cap_diff) {
                    valence > 0 ? (scalar += intensity_increase) : (scalar -= intensity_increase);
                }
                return scalar;
            }
            return 0.0;
        }
    }

    namespace analyzer {

        Influencer special_case_idioms = {
                {L"the shit", 3.0},
                {L"the bomb", 3.0},
                {L"bad ass", 1.5},
                {L"yeah right", -2.0},
                {L"cut the mustard", 2.0},
                {L"kiss of death", -1.5},
                {L"hand to mouth", -2.0}
        };

        /**
          * check for negation case using "least"
          * @param valence initial starting valence
          * @param words_and_emoticons list of text
          * @param i current word index
          * @return adapted valence
          */
        double least_check(double valence, const vector<wstring> &words_and_emoticons, unsigned long i) {
            if (i > 1 && !lexicon::contains(words_and_emoticons.at(i - 1)) && iequals(words_and_emoticons.at(i - 1), L"least")) {
                if (!iequals(words_and_emoticons.at(i - 2), L"at") && !iequals(words_and_emoticons.at(i - 2), L"very")) {
                    valence *= nscalar;
                }
            } else if (i > 0 && !lexicon::contains(words_and_emoticons.at(i -1)) && iequals(words_and_emoticons.at(i - 1), L"least")) {
                valence *= nscalar;
            }
            return valence;
        }

        /**
          * check for booster/dampener bi-grams such as 'sort of' or 'kind of'
          * @param valence initial starting valence
          * @param words_and_emoticons list of text
          * @param i current word index
          * @return adapted valence
          */
        double idioms_check(double valence, const vector<wstring> &words_and_emoticons, unsigned long i) {
            wstring onezero = str(wformat(L"%s %s") % words_and_emoticons.at(i-1) % words_and_emoticons.at(i));
            wstring twoonezero = str(wformat(L"%s %s %s") % words_and_emoticons.at(i-2) % words_and_emoticons.at(i-1) % words_and_emoticons.at(i));
            wstring twoone = str(wformat(L"%s %s") % words_and_emoticons.at(i-2) % words_and_emoticons.at(i-1));
            wstring threetwoone = str(wformat(L"%s %s %s") % words_and_emoticons.at(i-3) % words_and_emoticons.at(i-2) % words_and_emoticons.at(i-1));
            wstring threetwo = str(wformat(L"%s %s") % words_and_emoticons.at(i-3) % words_and_emoticons.at(i-2));
            vector<wstring> seq {onezero, twoonezero, twoone, threetwoone, threetwo};
            for (const auto &s: seq) {
                if (special_case_idioms.find(s) != special_case_idioms.end()) {
                    valence = special_case_idioms[s];
                    break;
                }
            }
            if (words_and_emoticons.size() - 1 > i) {
                wstring zeroone = str(wformat(L"%s %s") % words_and_emoticons.at(i) % words_and_emoticons.at(i + 1));
                if (special_case_idioms.find(zeroone) != special_case_idioms.end()) {
                    valence = special_case_idioms[zeroone];
                }
            }
            if (words_and_emoticons.size() -1 > i + 1) {
                wstring zeroonetwo = str(wformat(L"%s %s %s") % words_and_emoticons.at(i) % words_and_emoticons.at(i + 1) % words_and_emoticons.at(i + 2));
                if (special_case_idioms.find(zeroonetwo) != special_case_idioms.end()) {
                    valence = special_case_idioms[zeroonetwo];
                }
            }
            if (helpers::booster_dictionary.find(threetwo) != helpers::booster_dictionary.end() ||
                    helpers::booster_dictionary.find(twoone) != helpers::booster_dictionary.end()) {
                valence += helpers::booster_decrease;
            }
            return valence;
        }

        /**
         * check for negations from 'never'
         * @param valence initial starting valence
         * @param words_and_emoticons list of text
         * @param start_i processor index
         * @param i current word index
         * @return adapted valence
         */
        double never_check(double valence, const vector<wstring> &words_and_emoticons, unsigned long start_i, unsigned long i) {
            switch (start_i) {
                case 0: {
                    vector<wstring> vw{words_and_emoticons.at(i - 1)};
                    if (helpers::negated(vw)) {
                        valence *= nscalar;
                    }
                }; break;
                case 1: {
                    wstring im2 = words_and_emoticons.at(i - 2);
                    wstring im1 = words_and_emoticons.at(i - 1);
                    if (iequals(im2, L"never") && (iequals(im1, L"so") || iequals(im1, L"this"))) {
                        valence *= 1.5;
                    } else {
                        vector<wstring> vw{words_and_emoticons.at(i - (start_i + 1))};
                        if (helpers::negated(vw)) {
                            valence *= nscalar;
                        }
                    }
                }; break;
                case 2: {
                    wstring im3 = words_and_emoticons.at(i - 3);
                    wstring im2 = words_and_emoticons.at(i - 2);
                    wstring im1 = words_and_emoticons.at(i - 1);
                    if (iequals(im3, L"never") && (iequals(im2, L"so") || iequals(im2, L"this")) || (iequals(im1, L"so") || iequals(im1, L"this"))) {
                        valence *= 1.25;
                    } else {
                        vector<wstring> vw{words_and_emoticons.at(i - (start_i + 1))};
                        if (helpers::negated(vw)) {
                            valence *= nscalar;
                        }
                    }
                }; break;
                default:break;
            }
            return valence;
        }

        /**
         * check for added emphasis resulting from exclamation marks (up to 4 of them)
         * @param text to analyse
         * @return emphasis amplifier
         */
        double amplify_exclamation_marks(const wstring &text) {
            long ems = count(text.begin(), text.end(), L'!');
            return (ems > 4 ? 4 : ems) * 0.292;
        }

        /**
         * check for added emphasis resulting from question marks (2 or 3+)
         * @param text text to analyse
         * @return emphasis amplifier
         */
        double amplify_question_marks(const wstring &text) {
            long qms = count(text.begin(), text.end(), L'?');
            return qms > 1 ? qms <= 3 ? qms * 0.18 : 0.96 : 0.0;
        }

        /**
         * combined punctuation emphasis for exclamation and question marks
         * @param text to analyse
         * @return punctuation emphasis amplifier
         */
        double punctuation_emphasis(const wstring &text) {
            return amplify_exclamation_marks(text) + amplify_question_marks(text);
        }

        /**
         * compute sentiment valence of the word
         * @param words_and_emoticons list of text
         * @param word to analyse
         * @param i current word index
         * @return valence
         */
        double sentiment_valence(const vector<wstring> &words_and_emoticons, const wstring &word, unsigned long i) {
            bool cap_diff = helpers::all_caps_differential(words_and_emoticons);
            if (lexicon::contains(word)) {
                double valence = lexicon::score(word);
                if (all_of(word.begin(), word.end(), &::isupper) && cap_diff) {
                    if (valence > 0) {
                        valence += helpers::intensity_increase;
                    } else {
                        valence -= helpers::intensity_increase;
                    }
                }
                for (int x = 0; x < 3; x++) {
                    if (i > x && !lexicon::contains(words_and_emoticons.at(i - (x + 1)))) {
                        double scalar = helpers::determine_scalar(words_and_emoticons.at(i - (x + 1)), valence, cap_diff);
                        if (x == 1 && scalar != 0) {
                            scalar *= 0.95;
                        }
                        if (x == 2 && scalar != 0) {
                            scalar *= 0.9;
                        }
                        valence += scalar;
                        valence = never_check(valence, words_and_emoticons, static_cast<unsigned long>(x), i);
                        if (x == 2) {
                            valence = idioms_check(valence, words_and_emoticons, i);
                        }
                    }
                }
                return least_check(valence, words_and_emoticons, i);
            }
            return 0.0;
        }

        /**
         * compute our end scores
         * @param sentiments list of all sentiments
         * @param text original text
         * @return struct of negative neutral positive and compound sentiment
         */
        sentiment_score score_valence(vector<double> sentiments, const wstring &text) {
            if (sentiments.empty()) {
                return {};
            }
            double s_sum = 0, pos_sum = 0, neg_sum = 0, neu_count = 0;
            for (auto &s : sentiments) {
                s_sum += s;
                if (s > 0) {
                    pos_sum += (double(s) +1);
                }
                if (s < 0) {
                    neg_sum += (double(s) -1);
                }
                if (s == 0) {
                    neu_count++;
                }
            }
            double pe = punctuation_emphasis(text);
            if (s_sum > 0.0) {
                s_sum += pe;
            } else if (s_sum < 0.0) {
                s_sum -= pe;
            }
            double compound = helpers::normalize(s_sum);
            if (pos_sum > fabs(neg_sum)) {
                pos_sum += pe;
            } else if (pos_sum < fabs(neg_sum)) {
                neg_sum -= pe;
            }
            double total = pos_sum + fabs(neg_sum) + neu_count;
            sentiment_score result = sentiment_score();
            result.positive = fabs(pos_sum / total);
            result.negative = fabs(neg_sum / total);
            result.neutral = fabs(neu_count / total);
            result.compound = compound;
            return result;
        }

        vector<double> but_check(const vector<wstring> &words_and_emoticons, vector<double> sentiments) {
            for (unsigned long i = 0; i < words_and_emoticons.size(); i++) {
                if (iequals(words_and_emoticons.at(i), "but")) {
                    for (unsigned long j = 0; j < sentiments.size(); j++) {
                        if (j < i) {
                            double s = sentiments.at(j) * 0.5;
                            sentiments.erase(sentiments.begin() + j);
                            sentiments.insert(sentiments.begin() + j, s);
                        } else if (j > i) {
                            double s = sentiments.at(j) * 1.5;
                            sentiments.erase(sentiments.begin() + j);
                            sentiments.insert(sentiments.begin() + j, s);
                        }
                    }
                }
            }
            return sentiments;
        }

        sentiment_score polarity(const wstring &text) {
            vector<double> sentiments;
            vector<wstring> words_and_emoticons = text::words_and_emoticons(text);
            for (unsigned long i = 0; i < words_and_emoticons.size(); i++) {
                double valence = 0;
                wstring &item = words_and_emoticons.at(i);
                wstring item_lower = to_lower_copy(item);
                if ((i < words_and_emoticons.size() - 1 && iequals(item_lower, "kind") && iequals(words_and_emoticons.at(i+1), "of")) ||
                        helpers::booster_dictionary.find(item_lower) != helpers::booster_dictionary.end()) {
                    sentiments.push_back(valence);
                    continue;
                }
                sentiments.push_back(sentiment_valence(words_and_emoticons, item, i));
            }
            sentiments = but_check(words_and_emoticons, sentiments);
            return score_valence(sentiments, text);
        }
    }
}