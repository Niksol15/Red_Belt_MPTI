#include <utility>
#include <array>

using namespace std;

// TAirport should be enum with sequential items and last item TAirport::Last_
template <typename TAirport>
class AirportCounter {
public:
  // конструктор по умолчанию: список элементов пока пуст
  AirportCounter() = default;
  
  // конструктор от диапазона элементов типа TAirport
  template <typename TIterator>
  AirportCounter(TIterator begin, TIterator end){
      for(size_t i = 0; i < static_cast<size_t>(TAirport::Last_);++i){
          airports[i].first = static_cast<TAirport>(i);
      }
      for(auto it = begin; it != end; ++it){
          ++airports[static_cast<size_t>(*it)].second;
      }
  }

  // получить количество элементов, равных данному
  [[nodiscard]] size_t Get(TAirport airport) const{
      return airports[static_cast<size_t>(airport)].second;
  }

  // добавить данный элемент
  void Insert(TAirport airport){
      ++airports[static_cast<size_t>(airport)].second;
  }

  // удалить одно вхождение данного элемента
  void EraseOne(TAirport airport){
      --airports[static_cast<size_t>(airport)].second;
  }

  // удалить все вхождения данного элемента
  void EraseAll(TAirport airport){
      airports[static_cast<size_t>(airport)].second = 0;
  }

  using Item = pair<TAirport, size_t>;
  using Items = array<Item, static_cast<size_t>(TAirport::Last_)>;

    // получить некоторый объект, по которому можно проитерироваться,
    // получив набор объектов типа Item - пар (аэропорт, количество),
    // упорядоченных по аэропорту
  [[nodiscard]] Items GetItems() const{
        return airports;
  }

private:
  Items airports;
};
