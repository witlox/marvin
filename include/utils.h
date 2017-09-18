#ifndef MARVIN_UTILS_H
#define MARVIN_UTILS_H

#include <ctime>
#include <boost/date_time.hpp>

namespace bt = boost::posix_time;

const std::locale formats[] = {
        std::locale(std::locale::classic(),new bt::time_input_facet("%Y-%m-%d %H:%M:%S")),
        std::locale(std::locale::classic(),new bt::time_input_facet("%Y/%m/%d %H:%M:%S")),
        std::locale(std::locale::classic(),new bt::time_input_facet("%d.%m.%Y %H:%M:%S")),
        std::locale(std::locale::classic(),new bt::time_input_facet("%Y-%m-%d")),
        std::locale(std::locale::classic(),new bt::time_input_facet("%a, %d %m %Y %H:%M:%S z")),
};

std::time_t pt_to_time_t(const bt::ptime& pt)
{
    bt::ptime timet_start(boost::gregorian::date(1970,1,1));
    bt::time_duration diff = pt - timet_start;
    return diff.ticks()/bt::time_duration::rep_type::ticks_per_second;
}

time_t seconds_from_epoch(const std::string& s)
{
    bt::ptime pt;
    for (const auto &format : formats) {
        std::istringstream is(s);
        is.imbue(format);
        is >> pt;
        if(pt != bt::ptime()) break;
    }
    return pt_to_time_t(pt);
}

#endif //MARVIN_UTILS_H
