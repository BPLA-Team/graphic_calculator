#pragma once

// std libs
#include <string>
#include <vector>

namespace Math_func {

// MEANS: класс, который при конструировании модифицирует строку, обозначающую мат. функцию
// MEANS: класс, который хранит вектор всех номеров мат. функций, которые зависят от текущей
class expose_func_str {
 public:
  // ARGS: все мат. функции в виде строк, раскрываемая мат. функция в виде строки
  expose_func_str(const std::vector<std::string>& _all_funcs_str,
                  std::string& _func_str);

  // methods

  inline std::vector<size_t> get_dependences() { return dependences; }

  // ~methods

 private:
  // methods

  // DOES: раскрывает все зависимости, модифицируя строку
  // DOES: генерирует ошибки в том случае, если ввод инвалиден
  void expose_dep_func();

  // ~methods

  // vars

  // MEANS: вектор со всеми мат. функциями в виде строк
  std::vector<std::string> all_funcs_str;

  // MEANS: текущая мат. функция в виде строки
  std::string& func_str;

  // MEANS: общий вектор всех номеров мат. функций, которые зависят от текущей
  std::vector<size_t> dependences;

  // ~vars
};

}  // namespace Math_func