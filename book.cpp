#include <iomanip>
#include <iostream>
#include <map>

using namespace std;

class ReadingManager {
public:
    ReadingManager() = default;

    void Read(int user_id, int page_count) {
        if(id_to_page.count(user_id)){
            auto it = page_rating.find(id_to_page[user_id]);
            for(; it != page_rating.lower_bound(page_count); ++it){
                --(it->second);
            }
        } else {
            for(auto it = page_rating.lower_bound(page_count); it != page_rating.end(); ++it){
                ++(it->second);
            }
        }
        if(!page_rating.count(page_count)){
            page_rating[page_count] = 1;
            auto it = page_rating.find(page_count);
            if(it != page_rating.begin()){
                page_rating[page_count] += (--it) -> second;
            }
        }
        id_to_page[user_id] = page_count;
    }

    double Cheer(int user_id) const {
        if(!id_to_page.count(user_id)){
            return 0.0;
        } else if(id_to_page.size() == 1){
                return 1.0;
        } else {
            auto it = page_rating.find(id_to_page.at(user_id));
            if (it == page_rating.begin()){
                return 0.0;
            } else {
                return  ((--it) -> second) * 1.0 / (id_to_page.size() * 1.0 - 1.0);
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
