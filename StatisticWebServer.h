#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <set>
using namespace std;

class Stats {
public:
    Stats();
    void AddMethod(string_view method);
    void AddUri(string_view uri);
    const map<string_view, int>& GetMethodStats() const;
    const map<string_view, int>& GetUriStats() const;
private:
    map<string_view, int> method_status;
    map<string_view, int> uri_status;
    set<string_view> supported_methods = {"GET", "POST", "PUT", "DELETE"};
    set<string_view> supported_uri = {"/", "/order", "/product", "/basket", "/help"};
};

HttpRequest ParseRequest(string_view line);
