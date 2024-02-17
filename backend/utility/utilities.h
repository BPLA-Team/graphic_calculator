#pragma once

// std libs
#include <stack>
#include <string>
#include <vector>

namespace Backend_utilities {

// RETURNS: факт содержания символа в строке (bool)
// ARGS: символ, строка, в которой ищем
bool c_in_s(char c, const std::string& s);

// RETURNS: факт содержания элемента в векторе (bool)
// ARGS: элемент, вектор, в котором ищем
template <typename T>
bool elem_in_vec(T elem, const std::vector<T>& vec) {
  return find(vec.begin(), vec.end(), elem) != vec.end();
}

// RETURNS: символ, обозначающий строку (лексему)
// ARGS: строка (лексема)
char s_to_c(const std::string& s);

bool is_double(const std::string& str);

std::string spaces_deleted(const std::string& s);

// RETURNS: абсолютное значения числа
// ARGS: число типа double
// (чтобы избежать неявного преобразования, используя std::abs)
double absolute(double x);

// DOES: заменяет кусочек строки другим, модифицируя саму строку
// ARGS: строка, кусок строки (заменяемый), кусок строки (заменяющий)
void replace(std::string& str, const std::string& from, const std::string& to);

}  // namespace Backend_utilities