#pragma once

// std libs
#include <string>
#include <vector>

namespace Math_func {

/**
 * @brief Класс, который при иниц. мод. строку, обозначающую мат. функцию,
 * хранит все номера мат. функ., завис. от текущей
 */
class expose_func_str {
 public:
  /**
   * @brief Инициализирует новый экземпляр expose func_str
   * @param _all_funcs_str: все мат. функции
   * @param _func_str: раскрываемая мат. функция
   */
  expose_func_str(const std::vector<std::string>& _all_funcs_str,
                  std::string& _func_str);

  // methods

  inline std::vector<size_t> get_dependencies() { return dependencies; }

  // ~methods

 private:
  // methods

  /**
   * @brief Раскрывает все зависимости, модифицируя строку
   * @throw std::invalid_argument: том случае, если ввод инвалиден
   */
  void expose_dep_func();

  // ~methods

  // vars

  /// @brief Вектор со всеми мат. функциями в виде строк
  std::vector<std::string> all_funcs_str;

  /// @brief Текущая мат. функция в виде строки
  std::string& func_str;

  /// @brief Общий вектор всех номеров мат. функций, которые зависят от текущей
  std::vector<size_t> dependencies;

  // ~vars
};

}  // namespace Math_func