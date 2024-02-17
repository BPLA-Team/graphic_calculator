#pragma once

// std libs
#include <functional>
#include <string>
#include <vector>

// utility
#include "../utility/constants.h"

namespace Math_func {

// MEANS: математическая функция
class function {
 public:
  function() = default;

  // ARGS: строка, представляющая собой мат. функцию
  function(std::string _func_str);

  function(const function&);

  ~function() = default;

  // methods:

  // IDK: лямбда-выражения - это поля, которые я понимаю, как методы, но правильно ли это?

  // RETURNS: значение мат. функции
  // ARGS: значение x
  const std::function<double(double)> calculate = [this](double x) {
    return calc(x);
  };

  // RETURNS: значение мат. функции
  // ARGS: значение x
  inline double operator()(double x) const { return calc(x); }

  // RETURNS: значение производной мат. функции
  // ARGS: значение x
  const std::function<double(double)> differentiate = [this](double x) {
    return (calc(x + Backend_consts::delta_x) -
            calc(x - Backend_consts::delta_x)) /
           (2 * Backend_consts::delta_x);
  };

  // нету подходящего оператора для удобного получения производной :(

  bool has_var() const;

  // RETURNS: мат. функция в виде строки
  inline std::string get_func_str() const { return func_str; }

  function& operator=(const function&);

  // ~methods:

 private:
  // vars:

  // MEANS: мат. функция в виде строки
  std::string func_str;

  // MEANS: вектор лексем от мат. функции
  std::vector<std::string> lexs;

  // MEANS: вектор лексем, записанный в обратной польской нотации
  std::vector<std::string> rev_pol;

  // ~vars:

  // methods:

  // DOES: проверяет мат. функцию в виде строки, на валидность
  // DOES: генерирует ошибки в том случае, если ввод инвалиден
  // (правильное кол-во скобок, отсутствие лишних символов)
  // (правильное использование знаков, точек, цифр)
  void func_str_validation() const;

  // DOES: проверяет вектор лексем от мат. функции на валидность
  // DOES: генерирует ошибки в том случае, если ввод инвалиден
  // (правильное использование элементар. мат. функций (cos, sin, tan, exp, ln, um))
  // (отсутствие лишних переменных)
  void func_lexs_validation() const;

  // RETURNS: вектор лексем от мат. функции
  std::vector<std::string> lexemes() const;

  // RETURNS: вектор лексем, записанный в обратной польской нотации
  std::vector<std::string> reverse_polish() const;

  // RETURNS: значение мат. функции
  // ARGS: значение x
  double calc(double x) const;

  // ~methods:
};

}  // namespace Math_func
