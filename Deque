#include <stdexcept>
#include <vector>
using namespace std;

template <class T>
class Deque {
public:
    Deque() = default;
    bool Empty() const{
        return _head.empty() && _back.empty();
    }
    void PushBack(const T& t) {
        _back.push_back(t);
    }

    T& Back() {
        if(!_back.empty()){
            return _back.back();
        } else {
            return _head.front();
        }
    }
    const T& Back() const {
        if(!_back.empty()){
            return _back.back();
        } else {
            return _head.front();
        }
    }

    void PushFront(const T& t) {
        _head.push_back(t);
    }

    T& Front() {
        if(!_head.empty()){
            return _head.back();
        } else {
            return _back.front();
        }
    }
    const T& Front() const {
        if(!_head.empty()){
            return _head.back();
        } else {
            return _back.front();
        }
    }

    size_t Size() const {
        return _head.size() + _back.size();
    }

    T& operator[](size_t index) {
        if(index >= _head.size()){
            return _back[index - _head.size()];
        } else {
            return _head[_head.size() - 1 - index];
        }
    }
    const T& operator[](size_t index) const {
        if(index >= _head.size()){
            return _back[index - _head.size()];
        } else {
            return _head[_head.size() - 1 - index];
        }
    }
    T& At(size_t index) {
        if(index >= (_head.size() + _back.size())) {
            throw out_of_range("");
        } else {
            return this->operator[](index);
        }
    }
    const T& At(size_t index) const {
        if(index >= (_head.size() + _back.size())) {
            throw out_of_range("");
        } else {
            return this->operator[](index);
        }
    }
private:
    vector<T> _head;
    vector<T> _back;
};
