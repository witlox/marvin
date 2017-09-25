#include <cstring>
#include <vector>
#include <codecvt>

#include <libxml/parser.h>

#include <boost/format.hpp>
#include <boost/log/trivial.hpp>
#include <boost/algorithm/string.hpp>

#include "feeds.h"

using namespace std;
using namespace boost;

namespace feeds {

    wstring xml_char_to_wstring(const xmlChar *xml) {
        if (!xml) {
            BOOST_LOG_TRIVIAL(warning) << "provided xml string was null";
            return L"";
        }
        try {
            std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
            return convert.from_bytes((const char*) xml);
        }
        catch(const std::range_error& e)
        {
            BOOST_LOG_TRIVIAL(error) << format("xml conversion failed on %s") % e.what();
            return L"";
        }
    }

    wstring get_content(xmlNode *node) {
        wstring result;
        if (node) {
            xmlChar *content = xmlNodeGetContent(node);
            if (content) {
                result = xml_char_to_wstring(content);
                xmlFree(content);
            }
        }
        return result;
    }

    wstring get_prop(xmlNode *node, const char *prop) {
        wstring result;
        if (node) {
            xmlChar * value = xmlGetProp(node, (xmlChar *) prop);
            if (value) {
                result = xml_char_to_wstring(value);
                xmlFree(value);
            }
        }
        return result;
    }

    bool node_is(xmlNode *node, const char *name) {
        if (!node || !name || !node->name) {
            return false;
        }
        return strcmp((const char *)node->name, name) == 0;
    }


    feed_t parse(string url) {
        xmlDocPtr doc = xmlReadFile(url.c_str(), nullptr, XML_PARSE_RECOVER | XML_PARSE_NOERROR | XML_PARSE_NOWARNING);
        if (doc == nullptr){
            BOOST_LOG_TRIVIAL(error) << "could not parse buffer";
            return feed_t();
        }
        xmlNodePtr root_element = xmlDocGetRootElement(doc);
        feed_t f = feed_t();
        if (doc->encoding) {
            f.encoding = string(reinterpret_cast<const char *>(doc->encoding));
        }
        for (xmlNode *node = root_element->children; node != nullptr; node = node->next) {
            if (node_is(node, "channel")) {
                for (xmlNode *cnode = node->children; cnode != nullptr; cnode = cnode->next) {
                    if (node_is(cnode, "title")) {
                        f.title = get_content(cnode);
                        f.title_type = "text";
                    } else if (node_is(cnode, "link")) {
                        f.link = get_content(cnode);
                    } else if (node_is(cnode, "description")) {
                        f.description = get_content(cnode);
                    } else if (node_is(cnode, "pubDate")) {
                        f.pubDate = get_content(cnode);
                    } else if (node_is(cnode, "language")) {
                        f.language = get_content(cnode);
                    } else if (node_is(cnode, "item")) {
                        item_t it;
                        it.guid = get_prop(cnode, "about");
                        for (xmlNode *itnode = cnode->children; itnode != nullptr; itnode = itnode->next) {
                            if (node_is(itnode, "title")) {
                                it.title = get_content(itnode);
                                it.title_type = "text";
                            } else if (node_is(itnode, "link")) {
                                it.link = get_content(itnode);
                            } else if (node_is(itnode, "description")) {
                                it.description = get_content(itnode);
                                if (xmlChildElementCount(itnode) == 0) {
                                    it.description_type = (it.description.find_first_of('<') == string::npos) ? "text"
                                                                                                              : "html";
                                } else {
                                    it.description_type = "html";
                                }
                            } else if (node_is(itnode, "author")) {
                                it.author = get_content(itnode);
                            } else if (node_is(itnode, "author_email")) {
                                it.author_email = get_content(itnode);
                            } else if (node_is(itnode, "pubDate")) {
                                it.pubDate = get_content(itnode);
                            } else if (node_is(itnode, "guid")) {
                                it.guid = get_content(itnode);
                            } else if (node_is(itnode, "group")) {
                                for (xmlNode *mnode = itnode->children; mnode != nullptr; mnode = mnode->next) {
                                    if (node_is(mnode, "content")) {
                                        media_t media;
                                        media.media = get_prop(mnode, "url");
                                        media.type = get_prop(mnode, "medium");
                                        it.media.push_back(media);
                                    }
                                }
                            }
                        }
                        f.items.push_back(it);
                    }
                }
            }
        }
        xmlFreeDoc(doc);
        return f;
    }
}