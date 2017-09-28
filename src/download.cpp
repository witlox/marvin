#include <curl/curl.h>

#include <boost/format.hpp>
#include <boost/log/trivial.hpp>
#include <boost/algorithm/string.hpp>


#include "download.h"

using namespace std;
using namespace boost;

namespace download {

    static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
        size_t rsize = size * nmemb;
        auto *mem = (struct memory_block *) userp;

        mem->memory = static_cast<char *>(realloc(mem->memory, mem->size + rsize + 1));
        if (mem->memory == nullptr) {
            /* out of memory! */
            BOOST_LOG_TRIVIAL(error) << "not enough memory (realloc returned NULL)";
            return 0;
        }

        memcpy(&(mem->memory[mem->size]), contents, rsize);
        mem->size += rsize;
        mem->memory[mem->size] = 0;

        return rsize;
    }

    memory_block fetch_url(const string &url) {
        CURL *curl_handle;
        CURLcode res;

        struct memory_block chunk{};

        if (ends_with(url, ".png")) {
            chunk.type = png;
        } else if (ends_with(url, ".jpg") || ends_with(url, ".jpeg")) {
            chunk.type = jpg;
        } else if (ends_with(url, ".gif")) {
            chunk.type = gif;
        } else if (ends_with(url, ".bmp")) {
            chunk.type = bmp;
        } else {
            chunk.type = unkown;
        }

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
}