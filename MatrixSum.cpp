#include <vector>
#include <thread>
#include <cmath>
#include <future>
#include <numeric>
#include <functional>
using namespace std;

template <typename Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end)
            : first(begin)
            , last(end)
            , size_(distance(first, last))
    {
    }

    Iterator begin() const {
        return first;
    }

    Iterator end() const {
        return last;
    }

    size_t size() const {
        return size_;
    }

private:
    Iterator first, last;
    size_t size_;
};

template <typename Iterator>
class Paginator {
private:
    vector<IteratorRange<Iterator>> pages;

public:
    Paginator(Iterator begin, Iterator end, size_t page_size) {
        for (size_t left = distance(begin, end); left > 0; ) {
            size_t current_page_size = min(page_size, left);
            Iterator current_page_end = next(begin, current_page_size);
            pages.push_back({begin, current_page_end});

            left -= current_page_size;
            begin = current_page_end;
        }
    }

    auto begin() const {
        return pages.begin();
    }

    auto end() const {
        return pages.end();
    }

    size_t size() const {
        return pages.size();
    }
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
    return Paginator(begin(c), end(c), page_size);
}
template <typename ContainerOfVectors>
int64_t CalculateMatrixSumSingleThread(const ContainerOfVectors& matrix){
    int64_t res = 0;
    for(const auto& vec: matrix){
        res += accumulate(vec.begin(), vec.end(), 0);
    }
    return res;
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
    const size_t THREAD_COUNT = (std::thread::hardware_concurrency() == 0) ? 4 : std::thread::hardware_concurrency();
    const size_t PAGE_SIZE = ceil(matrix.size() * 1.0 / THREAD_COUNT);
    vector<future<int64_t>> futures;
    int64_t res = 0;
    for(auto& vv: Paginate(matrix, PAGE_SIZE)){
        futures.push_back(async([=](){return CalculateMatrixSumSingleThread (vv);}));
    }

    for(auto& f: futures){
        res += f.get();
    }
    return res;
}
