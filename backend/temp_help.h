// std libs
#include <iostream>
#include <vector>
using std::cout;
using std::endl;

#include "Math_func/function.h"

// TEMP: временная функция для простого дебага, удалить когда-нибудь

// RETURNS: поток ostream, в который вывели мат. функцию в виде строки
// ARGS: поток типа std::ostream, мат. функция
inline std::ostream& operator<<(std::ostream& os,
                                const Math_func::function& func) {
  return os << func.get_func_str();
}

// TEMP: временная функция для простого дебага, удалить когда-нибудь

// DOES: выводит все элементы вектора в консоль
template <typename T>
void print(const std::vector<T>& v) {
  cout << " size: " << v.size() << endl;
  cout << "{ ";
  for (size_t i = 0; i < v.size(); i++) {
    cout << "''" << v[i] << "''";
    if (i != v.size() - 1)
      cout << endl;
  }
  cout << " }" << endl;
}
