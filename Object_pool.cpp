#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
    T* Allocate(){
        T* pObj;
        if(!free_objects.empty()){
            pObj = free_objects.front();
            free_objects.pop();
        } else {
            pObj = new T;
        }
        allocate_objects.insert(pObj);
        return pObj;
    }
    T* TryAllocate(){
        if(!free_objects.empty()){
            T* pObj = free_objects.front();
            free_objects.pop();
            allocate_objects.insert(pObj);
            return pObj;
        } else {
            return nullptr;
        }
    }

    void Deallocate(T* object){
        if(allocate_objects.count(object)){
            free_objects.push(object);
            allocate_objects.erase(object);
        } else {
            throw invalid_argument("Object doesnt allocate");
        }
    }

    ~ObjectPool(){
        while (!free_objects.empty()){
            delete free_objects.front();
            free_objects.pop();
        }
        for(auto ptr: allocate_objects){
            delete ptr;
        }
    }

private:
    queue<T*> free_objects;
    set<T*> allocate_objects;
};
