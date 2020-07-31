#ifndef SIMPLE_VECTOR_H
#define SIMPLE_VECTOR_H

#include <cstdlib>
#include <algorithm>


template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;
    explicit SimpleVector(size_t size_):
        _begin(new T[size_]), size(size_), capacity(size_){}
    ~SimpleVector(){
        delete [] _begin;
    }

    T& operator[](size_t index){
        return _begin[index];
    }

    T* begin(){
        return _begin;
    }
    T* end(){
        return _begin + size;
    }

    size_t Size() const{
        return size;
    }
    size_t Capacity() const{
        return capacity;
    }
    void PushBack(const T& value){
        if(_begin == nullptr){
            _begin = new T[1];
            _begin[0] = value;
            size = 1;
            capacity = 1;
        } else if(size == capacity){
            capacity *= 2;
            T* temp = new T[capacity];
            for(size_t i = 0;  i != size; ++i){
                temp[i] = _begin[i];
            }
            delete [] _begin;
            _begin = temp;
            _begin[size] = value;
            ++size;
        } else {
            _begin[size] = value;
            ++size;
        }
    }

private:
    T* _begin = nullptr;
    size_t size = 0;
    size_t capacity = 0;
};

#endif
