#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <set>
#include <iterator>
#include <algorithm>

using namespace std;

class ReadingManager {
public:
    ReadingManager() = default;

    void Read(int user_id, int page_count) {
        if(id_to_page.count(user_id)){
            page_to_id[id_to_page[user_id]].erase(user_id);
        }
        id_to_page[user_id] = page_count;
        page_to_id[page_count].insert(user_id);
    }

    double Cheer(int user_id) const {
        if(!id_to_page.count(user_id)){
            return 0.0;
        } else {
            if(id_to_page.size() == 1){
                return 1.0;
            } else {
                int lower = 0;
                const map<int, set<int>>::const_iterator& it_end = page_to_id.lower_bound(id_to_page.at(user_id));
                map<int, set<int>>::const_iterator it = page_to_id.begin();
                for(;it != it_end; ++it){
                    lower += (it->second).size();
                }
                return lower * 1.0 / (id_to_page.size() - 1);
            }
        }
    }

private:
    //static const int MAX_USER_COUNT_ = 100'000;
    map<int, int> id_to_page;
    map<int, set<int>> page_to_id;
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }
    return 0;
}
