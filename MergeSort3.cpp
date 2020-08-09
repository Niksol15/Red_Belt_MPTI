#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if(range_end - range_begin < 2){
        return;
    }
    vector<typename RandomIt::value_type> vec(make_move_iterator(range_begin), make_move_iterator(range_end));
    auto it_one_third = vec.begin() + vec.size() / 3;
    auto it_two_third = it_one_third + vec.size() / 3;
    MergeSort(vec.begin(), it_one_third);
    MergeSort(it_one_third, it_two_third);
    MergeSort(it_two_third, vec.end());
    vector<typename RandomIt::value_type> temp;
    merge(make_move_iterator(vec.begin()), make_move_iterator(it_one_third),
          make_move_iterator(it_one_third), make_move_iterator(it_two_third),
          back_inserter(temp));
    merge(make_move_iterator(temp.begin()), make_move_iterator(temp.end()),
          make_move_iterator(it_two_third), make_move_iterator(vec.end()),
          range_begin);
}
