#include <algorithm>
using namespace std;

template <typename T>
void Swap(T* first, T* second){
    T temp = *first;
    *first = *second;
    *second = temp;
}

template <typename T>
void SortPointers(vector<T*>& pointers){
    sort(pointers.begin(), pointers.end(), [](T* a, T* b){ return *a < *b; });
}

template <typename T>
void ReversedCopy(T* source, size_t count, T* destination){
    T* temp = new T[count];
    reverse_copy(source, source + count, temp);
    copy(temp, temp + count, destination);
    delete [] temp;
}
