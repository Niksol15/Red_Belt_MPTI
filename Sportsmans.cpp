#include <iostream>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    int command_num;
    cin >> command_num;
    list<int> line;
    map<int, list<int>::iterator> pos;
    for(int i = 0; i < command_num; ++i){
        int first, second;
        cin >> first >> second;
        auto it = pos.find(second);
        if(it == pos.end()){
            line.push_back(first);
            pos[first] = prev(line.end());
        } else {
            line.insert(pos[second], first);
            pos[first] = prev(pos[second]);
        }
        
    }
    for(const auto& num: line){
        cout << num << '\n';
    }
    return 0;
}
