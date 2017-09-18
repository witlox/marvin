#include "download.h"
#include "utils.h"
#include <curl/curl.h>
#include <boost/format.hpp>
#include <boost/log/trivial.hpp>
#include <boost/algorithm/string.hpp>
#include "feeds.h"

using namespace std;
using namespace boost;

namespace download {

    struct MemoryStruct {
        char *memory;
        size_t size;
    };

    static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
        size_t rsize = size * nmemb;
        auto *mem = (struct MemoryStruct *) userp;

        mem->memory = static_cast<char *>(realloc(mem->memory, mem->size + rsize + 1));
        if (mem->memory == nullptr) {
            /* out of memory! */
            printf("not enough memory (realloc returned NULL)\n");
            return 0;
        }

        memcpy(&(mem->memory[mem->size]), contents, rsize);
        mem->size += rsize;
        mem->memory[mem->size] = 0;

        return rsize;
    }

    MemoryStruct fetch_url(const std::string &url) {
        CURL *curl_handle;
        CURLcode res;

        struct MemoryStruct chunk{};
        chunk.memory = static_cast<char *>(malloc(1));  /* will be grown as needed by the realloc above */
        chunk.size = 0;    /* no data at this point */
        curl_global_init(CURL_GLOBAL_ALL);
        curl_handle = curl_easy_init();
        curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *) &chunk);
        curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        curl_easy_setopt(curl_handle, CURLOPT_ENCODING, "gzip, deflate");
        res = curl_easy_perform(curl_handle);
        if (res != CURLE_OK) {
            BOOST_LOG_TRIVIAL(error) << format("curl_easy_perform() failed: %s") % curl_easy_strerror(res);
        } else {
            BOOST_LOG_TRIVIAL(debug) << format("%lu bytes retrieved") % (long) chunk.size;
        }
        curl_easy_cleanup(curl_handle);
        curl_global_cleanup();
        return chunk;
    }


    feed_t fetch_news(string source) {
        MemoryStruct chunk = fetch_url(source);

        // cleanup our source data
        string news(chunk.memory);
        erase_all(news, "\r");
        erase_all(news, "\n");

        feed_t result = feeds::parse(news, source);

        BOOST_LOG_TRIVIAL(info) << format("fetched %d items from %s") % result.items.size() % source;

        free(chunk.memory);
        return result;
    }
}