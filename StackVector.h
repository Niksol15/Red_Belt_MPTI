#ifndef STACK_VECTOR_H
#define STACK_VECTOR_H

#include <array>
#include <stdexcept>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0){
        if (a_size > N){
            throw invalid_argument("");
        } else {
            size = a_size;
        }
    }

    T& operator[](size_t index){
        return data[index];
    }
    const T& operator[](size_t index) const{
        return data[index];
    }

    auto begin(){
        return data.begin();
    }
    auto end(){
        data.begin() + size;
    }
    const auto begin() const{
        return data.begin();
    }
    const auto end() const{
        data.begin() + size;
    }

    size_t Size() const{
        return size;
    }
    size_t Capacity() const{
        return N;
    }

    void PushBack(const T& value){
        if(size == N){
            throw overflow_error("");
        } else {
            data[size] = value;
            ++size;
        }
    }

    T PopBack(){
        if(size){
            --size;
            return data[size];
        } else {
            throw underflow_error("");
        }
    }

private:
    array<T, N> data;
    size_t size;
};

#endif
