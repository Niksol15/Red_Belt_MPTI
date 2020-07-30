#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <cstdint>

using namespace std;

bool is_happen_in_last_day(int64_t current_time, int64_t time){
    return (time > (current_time - 86400)) && (time <= current_time);
};


struct Client{
    Client() = default;
    Client(int id, uint16_t count): client_id(id), room_count(count){}
    int client_id;
    uint16_t room_count;
};

class Hotel{
public:
    Hotel() = default;
    Hotel(int64_t time, int client_id, uint16_t room_count):
        total_room(room_count){
        last_day.push(make_pair(time, Client(client_id, room_count)));
        clients[client_id] = 1;
    }
    void Add(int64_t time, int id, uint16_t room_count){
        last_day.push(make_pair(time, Client(id, room_count)));
        total_room += room_count;
        if (clients.count(id)){
            ++clients[id];
        } else {
            clients[id] = 1;
        }
    }
    void update(int64_t current_time){
        while(!last_day.empty() && !is_happen_in_last_day(current_time, last_day.front().first)){
            total_room -= last_day.front().second.room_count;
            --clients[last_day.front().second.client_id];
            if(clients[last_day.front().second.client_id] == 0){
                clients.erase(last_day.front().second.client_id);
            }
            last_day.pop();
        }
    }
    uint64_t get_total_room() const{
        return total_room;
    }
    size_t get_total_client() const{
        return clients.size();
    }
private:
    queue<pair<int64_t, Client>> last_day;
    map<int, int> clients;
    uint64_t total_room = 0;
};

class BookingManager{
public:
    BookingManager() = default;
    void Book(int64_t time, const string& hotel_name, int client_id, uint16_t room_count){
        booking[hotel_name].Add(time, client_id, room_count);
        current_time = time;
    }

    size_t Clients(const string& hotel_name) {
        if(booking.count(hotel_name)){
            booking.at(hotel_name).update(current_time);
            return booking.at(hotel_name).get_total_client();
        } else {
            return 0;
        }

    }

    uint64_t Rooms(const string& hotel_name) {
        if(booking.count(hotel_name)){
            booking.at(hotel_name).update(current_time);
            return booking.at(hotel_name).get_total_room();
        } else {
            return 0;
        }
    }

private:
    map<string, Hotel> booking;
    int64_t current_time;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    BookingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        if (query_type == "BOOK") {
            int64_t time;
            cin >> time;
            string hotel_name;
            cin >> hotel_name;
            int client_id, room_count ;
            cin >> client_id >> room_count;
            manager.Book(time, hotel_name, client_id, room_count);
        } else if (query_type == "CLIENTS") {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.Clients(hotel_name) << "\n";
        } else if (query_type == "ROOMS") {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.Rooms(hotel_name) << "\n";
        }
    }
    return 0;
}
