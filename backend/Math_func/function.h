#pragma once

// std libs
#include <functional>
#include <string>
#include <vector>

// utility
#include "../utility/constants.h"

namespace Math_func {

/// @brief Математическая функция
class function {
 public:
  function() = default;

  /**
   * @brief Инициализирует новый экземпляр function
   * @param _func_str: строка, представляющая собой мат. функцию
   */
  function(std::string _func_str);

  function(const function&);

  ~function() = default;

  // methods:

  // TODO: избавиться от лямбд как от полей

  /// @brief Значение мат. функции
  const std::function<double(double)> calculate = [this](double x) {
    return calc(x);
  };

  /**
   * @brief: Значение мат. функции
   * @param x
   * @return double
   */
  inline double operator()(double x) const { return calc(x); }

  /// @brief Значение производной мат. функции
  const std::function<double(double)> differentiate = [this](double x) {
    return (calc(x + Backend_consts::delta_x) -
            calc(x - Backend_consts::delta_x)) /
           (2 * Backend_consts::delta_x);
  };

  // нету подходящего оператора для удобного получения производной :(

  bool has_var() const;

  /**
   * @brief Возвращает значение мат. функции в виде строки
   * @return std::string: строка
   */
  inline std::string get_func_str() const { return func_str; }

  function& operator=(const function&);

  // ~methods:

 private:
  // vars:

  /// @brief Мат. функция в виде строки
  std::string func_str;

  /// @brief Вектор лексем от мат. функции
  std::vector<std::string> lexs;

  /// @brief Вектор лексем, записанный в обратной польской нотации
  std::vector<std::string> rev_pol;

  // ~vars:

  // methods:

  /**
   * @brief Проверяет мат. функцию в виде строки, на валидность
   * @details Правильное кол-во скобок, отсутствие лишних символов, правильное
   * использование знаков, точек, цифр)
   * @throw std::invalid_argument: в том случае, если ввод инвалиден
   */
  void func_str_validation() const;

  /**
   * @brief Проверяет вектор лексем от мат. функции на валидность
   * @details Правильное использование элементарной мат. функций (типа exp, sin,
   * ln), отсутствие лишних переменных
   * @throw std::invalid_argument: в том случае, если ввод инвалиден
   */
  void func_lexs_validation() const;

  std::vector<std::string> lexemes() const;

  std::vector<std::string> reverse_polish() const;

  /**
   * @brief Значение мат. функции
   * @param x
   * @return double
   */
  double calc(double x) const;

  // ~methods:
};

}  // namespace Math_func
