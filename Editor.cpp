#include <string>
#include <iterator>
#include <list>
using namespace std;

class Editor {
public:
    Editor() = default;
    void Left(){
        if(cursor != text.begin()){
            cursor = prev(cursor);
        }
    }
    void Right(){
        if(cursor != text.end()){
            cursor = next(cursor);
        }
    }
    void Insert(char token){
        cursor = text.insert(cursor, token);
        cursor = next(cursor);
    }
    void Cut(size_t tokens = 1){
        Copy(tokens);
        while(tokens > 0 && cursor != text.end()){
            cursor = text.erase(cursor);
            --tokens;
        }
    }
    void Copy(size_t tokens = 1){
        buffer.clear();
        for (auto it = cursor; tokens > 0 && it != text.end(); ++it){
            buffer.push_back(*it);
            --tokens;
        }
    }
    void Paste(){
        cursor = text.insert(cursor, buffer.begin(), buffer.end());
        cursor = next(cursor, buffer.size());
    }
    [[nodiscard]]  string GetText() const{
        return string(text.begin(), text.end());
    }

private:
    list<char> text;
    list<char> buffer;
    list<char>::iterator cursor = text.end();
};
