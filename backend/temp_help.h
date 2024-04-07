// std libs
#include <iostream>
#include <vector>
using std::cout;
using std::endl;

#include "Math_func/function.h"

/// @file TEMP: Временные функция для простого дебага, удалить когда-нибудь

/**
 * @return std::ostream&: поток, в который вывели мат. функцию в виде строки
 * @param os: поток типа std::ostream
 * @param func: мат. функция
 */
inline std::ostream& operator<<(std::ostream& os,
                                const Math_func::function& func) {
  return os << func.get_func_str();
}

/**
 * @brief Выводит все элементы вектора в консоль
 * @tparam T: тип, у которого определена операция вывода
 * @param v: вектор
 */
template <typename T>
void print(const std::vector<T>& v) {
  cout << " size: " << v.size() << endl;
  cout << "{ ";
  for (size_t i = 0; i < v.size(); i++) {
    cout << "''" << v[i] << "''";
    if (i != v.size() - 1) cout << endl;
  }
  cout << " }" << endl;
}
