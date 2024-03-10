#pragma once

// std libs
#include <string>
#include <vector>

namespace Math_func {

// MEANS: класс, который при иниц. мод. строку, обозначающую мат. функцию
// MEANS: класс, который хранит все номера мат. функ., завис. от текущей
class expose_func_str {
 public:
  // ARGS: все мат. функции, раскрываемая мат. функция
  // (в виде строк)
  expose_func_str(const std::vector<std::string>& _all_funcs_str,
                  std::string& _func_str);

  // methods

  inline std::vector<size_t> get_dependencies() { return dependencies; }

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
  std::vector<size_t> dependencies;

  // ~vars
};

}  // namespace Math_func