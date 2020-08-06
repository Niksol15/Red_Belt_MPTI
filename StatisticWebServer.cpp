#include "stats.h"

void Parse(string_view& token, string_view& line){
    size_t token_end = line.find(' ');
    token = line.substr(0, token_end);
    line.remove_prefix(token_end + 1);
}

HttpRequest ParseRequest(string_view line){
    HttpRequest res;
    size_t begin = line.find_first_not_of(' ');
    line.remove_prefix(begin);
    Parse(res.method, line);
    Parse(res.uri, line);
    res.protocol = line;
    return res;
}

Stats::Stats() {
    for(auto& s: supported_methods){
        method_status[s] = 0;
    }
    method_status["UNKNOWN"] = 0;
    for(auto& s: supported_uri){
        uri_status[s] = 0;
    }
    uri_status["unknown"] = 0;
}

void Stats::AddMethod(string_view method) {
    if(supported_methods.find(method) != supported_methods.end()){
        ++method_status[method];
    } else {
        ++method_status["UNKNOWN"];
    }
}

void Stats::AddUri(string_view uri) {
    if(supported_uri.find(uri) != supported_uri.end()){
        ++uri_status[uri];
    } else {
        ++uri_status["unknown"];
    }
}

const map<string_view, int>& Stats::GetMethodStats() const {
    return method_status;
}

const map<string_view, int>& Stats::GetUriStats() const {
    return uri_status;
}
