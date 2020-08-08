include <set>
#include <map>
#include <string>
#include <vector>

using namespace std;

template <typename String>
using Group = vector<String>;

template <typename String>
using Char = typename String::value_type;

template <typename String>
using Key = String;


template <typename String>
Key<String> ComputeStringKey(String& string) {
    set<Char<String>> res;
    for(auto& ch: string){
        res.insert(move(ch));
    }
    return Key<String>(res.begin(), res.end());
}


template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
    map<Key<String>, Group<String>> groups_map;
    for (String& string : strings) {
        groups_map[ComputeStringKey(string)].push_back(move(string));
    }
    vector<Group<String>> groups;
    for (auto& [key, group] : groups_map) {
        groups.push_back(move(group));
    }
    return groups;
}
