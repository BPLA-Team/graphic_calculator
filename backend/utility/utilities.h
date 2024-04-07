#pragma once

// std libs
#include <stack>
#include <string>
#include <vector>

namespace Backend_utilities {

/**
 * @param c: символ
 * @param s: строка, в которой ищем
 * @return bool: факт содержания символа в строке
 */
bool c_in_s(char c, const std::string& s);

/**
 * @tparam T: тип элемента в векторе
 * @param elem: элемент
 * @param vec: вектор, в котором ищем
 * @return bool: факт содержания элемента в векторе
 */
template <typename T>
bool elem_in_vec(T elem, const std::vector<T>& vec) {
  return find(vec.begin(), vec.end(), elem) != vec.end();
}

/**
 * @param s: строка (лексема)
 * @return char: символ, обозначающий строку (лексему)
 */
char s_to_c(const std::string& s);

bool is_double(const std::string& str);

std::string spaces_deleted(const std::string& s);

/**
 * @brief Абсолютное значения числа
 * @param x: число типа double
 * @return double
 */
double absolute(double x);

/**
 * @brief Заменяет кусочек строки другим, модифицируя саму строку
 *
 * @param str: строка
 * @param from: кусок строки (заменяемый)
 * @param to: кусок строки (заменяющий)
 */
void replace(std::string& str, const std::string& from, const std::string& to);

}  // namespace Backend_utilities