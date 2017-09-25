#include <cwchar>
#include <cmath>

#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>

#include "catch.hpp"
#include "utils.h"
#include "lexicon.h"
#include "feeds.h"
#include "smiley.h"
#include "emoji.h"
#include "sentiment.h"

using namespace std;
using namespace boost;

TEST_CASE("we can convert a date string to something more internal") {
    REQUIRE(utils::seconds_from_epoch("Wed, 20 Sep 2017 13:38:41 GMT") == 9223372036854);
}

TEST_CASE("we can determine an intersect") {
    vector<wstring> a {L"A", L"B"};
    vector<wstring> b {L"B", L"C"};
    REQUIRE(utils::intersection(a, b).size() == 2);
    REQUIRE(utils::intersection(a, b)[0] == L"A");
    REQUIRE(utils::intersection(a, b)[1] == L"C");
}

TEST_CASE("we can download stuff from the web") {
    feed_t cnn_results = feeds::parse("http://rss.cnn.com/rss/edition.rss");
    REQUIRE(!cnn_results.items.empty());
}

TEST_CASE("score stuff based on our lexicon") {
    REQUIRE(lexicon::score(L"worthless") == -1.9f);
    REQUIRE(lexicon::score(L"thingymagicblabla") == 0);
}

TEST_CASE("smileys can be detected") {
    REQUIRE(smiley::is_smiley(L":)"));
    REQUIRE(smiley::is_positive(L":)"));
    REQUIRE(smiley::is_negative(L":("));
}

TEST_CASE("emojis can be identified") {
    REQUIRE(iequals(emoji::get_text(L"⚓").c_str(), L"anchor"));
    REQUIRE(iequals(emoji::get_text(L"bla").c_str(), L"bla"));
}

TEST_CASE("messy text can be cleaned") {
    vector<wstring> expectation {L"the", L"cat", L"with", L":)", L"the", L"hat"};
    vector<wstring> result = sentiment::text::words_and_emoticons(L".the cat, with :) the hat.");
    for (int i = 0; i < expectation.size(); i++) {
        REQUIRE(result[i] == expectation[i]);
    }
}

TEST_CASE("we can identify partially caps text (full word)") {
    REQUIRE(sentiment::helpers::all_caps_differential(vector<wstring> {L"BLA", L"bla"}));
    REQUIRE(!sentiment::helpers::all_caps_differential(vector<wstring> {L"BLA"}));
    REQUIRE(!sentiment::helpers::all_caps_differential(vector<wstring> {L"bla"}));
}

TEST_CASE("we can evaluate negation within sentinces") {
    REQUIRE(!sentiment::helpers::negated(vector<wstring>()));
    REQUIRE(sentiment::helpers::negated(vector<wstring>{L"not", L"bad"}));
    REQUIRE(sentiment::helpers::negated(vector<wstring>{L"shouldn't", L"be", L"bad"}));
}

inline double round3( double val ) {
    stringstream ss;
    ss << fixed << setprecision(3) << val;
    return atof(ss.str().c_str());
}

inline double round4( double val ) {
    stringstream ss;
    ss << fixed << setprecision(4) << val;
    return atof(ss.str().c_str());
}

bool compare_sentiment(sentiment::analyzer::sentiment_score a, sentiment::analyzer::sentiment_score b) {
    return round3(a.positive) == b.positive && round3(a.negative) == b.negative && round3(a.neutral) == b.neutral && round4(a.compound) == b.compound;
}

TEST_CASE("sentiment analysis should work for simple sentences") {
    REQUIRE(compare_sentiment(sentiment::analyzer::polarity(L"VADER is smart, handsome, and funny."), sentiment::analyzer::sentiment_score { 0.746, 0.0, 0.254, 0.8316 }));
    REQUIRE(compare_sentiment(sentiment::analyzer::polarity(L"VADER is not smart, handsome, nor funny."), sentiment::analyzer::sentiment_score { 0.0, 0.646, 0.354, -0.7424 }));
    REQUIRE(compare_sentiment(sentiment::analyzer::polarity(L"VADER is smart, handsome, and funny!"), sentiment::analyzer::sentiment_score { 0.752, 0.0, 0.248, 0.8439 }));
    REQUIRE(compare_sentiment(sentiment::analyzer::polarity(L"VADER is very smart, handsome, and funny."), sentiment::analyzer::sentiment_score { 0.701, 0.0, 0.299, 0.8545 }));
    REQUIRE(compare_sentiment(sentiment::analyzer::polarity(L"VADER is VERY SMART, handsome, and FUNNY."), sentiment::analyzer::sentiment_score { 0.754, 0.0, 0.246, 0.9227 }));
    REQUIRE(compare_sentiment(sentiment::analyzer::polarity(L"VADER is VERY SMART, handsome, and FUNNY!!!"), sentiment::analyzer::sentiment_score { 0.767, 0.0, 0.233, 0.9342 }));
    REQUIRE(compare_sentiment(sentiment::analyzer::polarity(L"VADER is VERY SMART, uber handsome, and FRIGGIN FUNNY!!!"), sentiment::analyzer::sentiment_score { 0.706, 0.0, 0.294, 0.9469 }));
    REQUIRE(compare_sentiment(sentiment::analyzer::polarity(L"The book was good."), sentiment::analyzer::sentiment_score { 0.492, 0.0, 0.508, 0.4404 }));
    REQUIRE(compare_sentiment(sentiment::analyzer::polarity(L"The book was kind of good."), sentiment::analyzer::sentiment_score { 0.343, 0.0, 0.657, 0.3832 }));
    REQUIRE(compare_sentiment(sentiment::analyzer::polarity(L"The plot was good, but the characters are uncompelling and the dialog is not great."), sentiment::analyzer::sentiment_score { 0.094, 0.327, 0.579, -0.7042 }));
    REQUIRE(compare_sentiment(sentiment::analyzer::polarity(L"At least it isn't a horrible book."), sentiment::analyzer::sentiment_score { 0.363, 0.0, 0.637, 0.431 }));
    REQUIRE(compare_sentiment(sentiment::analyzer::polarity(L"Make sure you :) or :D today!"), sentiment::analyzer::sentiment_score { 0.69, 0.0, 0.31, 0.8356 }));
    REQUIRE(compare_sentiment(sentiment::analyzer::polarity(L"Today SUX!"), sentiment::analyzer::sentiment_score { 0.0, 0.779, 0.221, -0.5461 }));
    REQUIRE(compare_sentiment(sentiment::analyzer::polarity(L"Today only kinda sux! But I'll get by, lol"), sentiment::analyzer::sentiment_score { 0.251, 0.179, 0.569, 0.2228 }));
}

TEST_CASE("sentiment analysis should work for more tricky sentences") {
    REQUIRE(compare_sentiment(sentiment::analyzer::polarity(L"Sentiment analysis has never been good."), sentiment::analyzer::sentiment_score { 0.0, 0.325, 0.675, -0.3412 }));
    REQUIRE(compare_sentiment(sentiment::analyzer::polarity(L"Sentiment analysis has never been this good!"), sentiment::analyzer::sentiment_score { 0.379, 0.0, 0.621, 0.5672 }));
    REQUIRE(compare_sentiment(sentiment::analyzer::polarity(L"Most automated sentiment analysis tools are shit."), sentiment::analyzer::sentiment_score { 0.0, 0.375, 0.625, -0.5574 }));
    REQUIRE(compare_sentiment(sentiment::analyzer::polarity(L"With VADER, sentiment analysis is the shit!"), sentiment::analyzer::sentiment_score { 0.417, 0.0, 0.583, 0.6476 }));
    REQUIRE(compare_sentiment(sentiment::analyzer::polarity(L"Other sentiment analysis tools can be quite bad."), sentiment::analyzer::sentiment_score { 0.0, 0.351, 0.649, -0.5849 }));
    REQUIRE(compare_sentiment(sentiment::analyzer::polarity(L"On the other hand, VADER is quite bad ass!"), sentiment::analyzer::sentiment_score { 0.586, 0.0, 0.414, 0.8172 }));
    REQUIRE(compare_sentiment(sentiment::analyzer::polarity(L"Roger Dodger is one of the most compelling variations on this theme."), sentiment::analyzer::sentiment_score { 0.166, 0.0, 0.834, 0.2944 }));
    REQUIRE(compare_sentiment(sentiment::analyzer::polarity(L"Roger Dodger is one of the least compelling variations on this theme."), sentiment::analyzer::sentiment_score { 0.0, 0.132, 0.868, -0.1695 }));
    REQUIRE(compare_sentiment(sentiment::analyzer::polarity(L"Roger Dodger is at least compelling as a variation on the theme."), sentiment::analyzer::sentiment_score { 0.16, 0.0, 0.84, 0.2263 }));
}