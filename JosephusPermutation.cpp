#include <iterator>
#include <list>

using namespace std;

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
    list<typename RandomIt::value_type> pool;
    move(first, last, back_inserter(pool));
    auto it = pool.begin();
    while(!pool.empty()){
        *(first++) = move(*it);
        it = pool.erase(it);
        for(size_t i = 0; i < step_size - 1; ++i){
            if(it == pool.end()){
                it = pool.begin();
            }
            ++it;
        }
        if(it == pool.end()){
            it = pool.begin();
        }
    }
}
