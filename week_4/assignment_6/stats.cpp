//
// Created by d.eroshenkov on 29.01.2019.
//

#include "stats.h"

#include <string_view>
#include <map>
#include <algorithm>

using namespace std;

Stats::Stats()
{
    for (const auto &item : METHODS)
    {
        method_stats_[item] = 0;
    }

    for (const auto &item : URIS)
    {
        uri_stats_[item] = 0;
    }
}

void Stats::AddMethod(string_view method)
{
    auto item = find(METHODS.begin(), METHODS.end(), string(method));
    if (item == METHODS.end())
    {
        item = &METHODS.back();
    }

    method_stats_[*item]++;
}

void Stats::AddUri(string_view uri)
{
    auto item = find(URIS.begin(), URIS.end(), string(uri));
    if (item == URIS.end())
    {
        item = &URIS.back();
    }

    uri_stats_[*item]++;
}

const map<string_view, int> &Stats::GetMethodStats() const
{
    return method_stats_;
}

const map<string_view, int> &Stats::GetUriStats() const
{
    return uri_stats_;
}

HttpRequest ParseRequest(string_view str)
{
    HttpRequest result = {};
    size_t first_not_space = str.find_first_not_of(" ");
    str.remove_prefix(first_not_space);
    size_t space = str.find(" ");
    result.method = str.substr(0, space);
    if (space == str.npos)
    {
        return result;
    }
    str.remove_prefix(space + 1);

    space = str.find(' ');
    result.uri = str.substr(0, space);
    if (space == str.npos)
    {
        return result;
    }
    str.remove_prefix(space + 1);

    space = str.find(' ');
    result.protocol = str.substr(0, space);

    return result;
}