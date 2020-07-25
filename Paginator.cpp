#include <numeric>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

template <typename Iterator>
class Page{
public:
    Page() = default;
    Page(const Iterator& begin, const Iterator& end): first(begin), last(end){}
    size_t size() const{
        return last - first;
    }
    Iterator begin() const{
        return first;
    }
    Iterator end() const{
        return last;
    }
private:
    Iterator first;
    Iterator last;
};

template <typename Iterator>
class Paginator {
public:
    Paginator() = default;
    Paginator(const Iterator& begin, const Iterator& end, size_t page_size){
        for(Iterator it = begin; it < end; it += page_size){
            _pages.push_back(Page(it, min(end, it + page_size)));
        }
    }
    auto begin() const{
        return _pages.begin();
    }
    auto end() const{
        return _pages.end();
    }
    size_t size() const{
        return _pages.size();
    }
private:
    vector<Page<Iterator>> _pages;
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
    return Paginator(c.begin(), c.end(), page_size);
}
