#include "expose_func_str.h"

// std libs
#include <algorithm>
#include <stack>
#include <stdexcept>
using std::find;
using std::invalid_argument;
using std::stack;
using std::string;
using std::vector;

// utility
#include "../utility/utilities.h"
using namespace Backend_utilities;

namespace Math_func {

expose_func_str::expose_func_str(const vector<string>& _all_funcs_str,
                                 string& _func_str)
    : all_funcs_str{_all_funcs_str}, func_str{_func_str} {
  expose_dep_func();
}

void expose_func_str::expose_dep_func() {
  func_str = spaces_deleted(func_str);

  // MEANS: вектор для записи зависимости, которая еще не дошла до выражения без y_n
  vector<size_t> unexposed_dependences;

  // если 'y' нету, то и делать ничего не надо
  if (!c_in_s('y', func_str))
    return;

  // в строке есть y, но за ним нету номера
  if (func_str.find("y_") == string::npos)
    throw invalid_argument("invalid usage 'y'");

  // y_n стоит в конце
  if (func_str.rfind('y') > func_str.size() - 3)
    throw invalid_argument("invalid usage 'y'");

  // иначе проходимся по строке до тех пор, пока в ней не будут раскрыты все y_n
  // (мы проходимся не рекурсией, а динамически: подтаскиваем все раскрытия y_n сразу)
  for (size_t i = 0; i < func_str.size(); i++) {
    // MEANS: текущий символ
    char ch = func_str[i];

    if (ch == 'y') {
      // MEANS: считываемый предполагаемый номер мат. функции
      // (на данном моменте может оказаться не валидным)
      string readed_est_number = "";

      // склеиваем все цифры кроме нуля, которые идут после '_'
      for (size_t j = i + 2; j < func_str.size(); j++)
        if (isdigit(func_str[j]) && func_str[j] != '0')
          readed_est_number += func_str[j];
        else
          break;  // (дальше пошли не цифры)

      // не считали, значит, это был либо 0, либо что-то иное
      if (readed_est_number.empty())
        throw invalid_argument("invalid function number");

      // MEANS: номер предполагаемой мат. функции в общем векторе
      size_t est_number = stoull(readed_est_number);

      // MEANS: индекс предполагаемой мат. функции в общем векторе
      size_t est_index = est_number - 1;

      // номер больше количества возможных к вводу мат. функций
      if (est_number > all_funcs_str.size())
        throw invalid_argument("invalid function number: " + readed_est_number);

      // встретили внутри вектора еще не до конца раскрытых зависимостей повтор номера
      if (elem_in_vec(est_number, unexposed_dependences))
        throw invalid_argument("self-usage or loop");

      // если новое раскрытие содержит y - значит, оно не полное
      if (c_in_s('y', all_funcs_str[est_index]))
        unexposed_dependences.push_back(est_number);
      // если не содержит, то раскрыли веточку
      else
        unexposed_dependences.clear();

      // если неполных раскрытий с этим номером не было, добавляем его в общий список
      // (таким образом в общем списке не будет повторов)
      if (!elem_in_vec(est_number, dependences))
        dependences.push_back(est_number);

      // заменяем в func_str выражение y_n на то, что оно означает
      // (заключаем в скобки, чтобы не нарушать мат. порядок действий)

      // TODO: выводить полный тип ошибки только в боксе первичной мат. функции, где нету y_n
      // TODO: а во всех остальных просто писать, что такая-то такая ошибочна

      // пустая строка - самая очевидная ошибка, её менять нету смысла
      if (!all_funcs_str[est_index].empty())
        Backend_utilities::replace(func_str, "y_" + readed_est_number,
                                   '(' + all_funcs_str[est_index] + ')');
      else
        func_str = all_funcs_str[est_index];
    }
  }
}

}  // namespace Math_func