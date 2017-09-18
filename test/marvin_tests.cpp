#include "catch.hpp"
#include "feeds.h"
#include "download.h"

using namespace std;
using namespace download;

TEST_CASE("we can parse valid rss feeds") {
    std::string parsable = "<rss><channel><item><title>test</title></item></channel></rss>";
    feed_t result = feeds::parse(parsable, "");
    REQUIRE(result.items.size() == 1);
    REQUIRE(result.items[0].title == "test");
}

TEST_CASE("we can parse valid rss media") {
    std::string parsable = R"(<rss><channel><item><title>test</title><media:group><media:content medium="image" url="test.png"/></media:group></item></channel></rss>)";
    feed_t result = feeds::parse(parsable, "");
    REQUIRE(result.items.size() == 1);
    REQUIRE(result.items[0].media.size() == 1);
    REQUIRE(result.items[0].media[0].type == "image");
    REQUIRE(result.items[0].media[0].media == "test.png");
}


TEST_CASE("we can download stuff from the web", "[fetch_news]") {
    feed_t cnn_results = fetch_news("http://rss.cnn.com/rss/edition.rss");
    REQUIRE(!cnn_results.items.empty());
}
