#include <iomanip>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class ReadingManager {
public:
    ReadingManager() = default;

    void Read(int user_id, int page_count) {
        if(id_to_page.count(user_id)){
            --page_rating[id_to_page[user_id]];
        }
        id_to_page[user_id] = page_count;
        if(!page_rating.count(page_count)) {
            page_rating[page_count] = 1;
        } else {
            ++page_rating[page_count];
        }
    }

    double Cheer(int user_id) const {
        if(!id_to_page.count(user_id)){
            return 0.0;
        } else {
            if(id_to_page.size() == 1){
                return 1.0;
            } else {
                int lower = 0;
                auto it_end = page_rating.lower_bound(id_to_page.at(user_id));
                for(auto it = page_rating.begin();it != it_end; ++it){
                    lower += it->second;
                }
                return lower * 1.0 / (id_to_page.size() - 1);
            }
        }
    }

private:
    map<int, int> id_to_page;
    map<int, int> page_rating;
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
