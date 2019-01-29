#pragma once

#include "http_request.h"

#include <string_view>
#include <map>

class Stats
{
public:
    Stats();
    void AddMethod(string_view method);
    void AddUri(string_view uri);
    const map<string_view, int> &GetMethodStats() const;
    const map<string_view, int> &GetUriStats() const;
private:
    const array<string, 5> METHODS = {"GET", "POST", "PUT", "DELETE", "UNKNOWN"};
    const array<string, 6> URIS = {"/", "/order", "/product", "/basket", "/help", "unknown"};

    map<string_view, int> uri_stats_;
    map<string_view, int> method_stats_;
};

HttpRequest ParseRequest(string_view line);