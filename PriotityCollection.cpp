#include "test_runner.h"
#include <iterator>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class PriorityCollection {
public:
    using Id = int;

    Id Add(T object){
        collection.emplace_back(Node(move(object)));
        priority.insert({0, collection.size() - 1});
        return collection.size() - 1;
    }

    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
             IdOutputIt ids_begin){
        while (range_begin != range_end){
            *ids_begin++ = Add(move(*range_begin++));
        }
    }

    bool IsValid(Id id) const{
        return (0 <= id) && (id < collection.size()) && collection[id].priority != deleted_el_priority;
    }

    [[nodiscard]] const T& Get(Id id) const{
        return collection[id].data;
    }

    void Promote(Id id){
        priority.erase({collection[id].priority, id});
        ++collection[id].priority;
        priority.insert({collection[id].priority, id});
    }

    [[nodiscard]] pair<const T&, int> GetMax() const{
        return {collection[priority.rbegin()->second].data, priority.rbegin()->first};
    }

    pair<T, int> PopMax(){
        int delete_id = priority.rbegin()->second;
        auto res = make_pair(move(collection[delete_id].data), collection[delete_id].priority);
        collection[delete_id].priority = deleted_el_priority;
        priority.erase({priority.rbegin()->first, delete_id});
        priority.insert({-1, delete_id});
        return res;
    }

private:
    struct Node{
        explicit Node(T&& object): data(move(object)), priority(0){}
        T data;
        int priority;
    };
    set<pair<int, Id>> priority;
    vector<Node> collection;
    static const int deleted_el_priority = -1;
};
