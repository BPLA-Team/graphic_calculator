
#include "function.h"

// std libs
#include <algorithm>
#include <stdexcept>
using std::count;
using std::invalid_argument;
using std::string;
using std::vector;

// utility
#include "../utility/utilities.h"
using namespace Backend_utilities;
using namespace Backend_consts;

namespace Math_func {

// TODO: полностью переписать эту дичь, используя string::find

void function::func_str_validation() const {
  // проверка на пустую строку
  if (func_str == "") throw invalid_argument("empty expression");

  /// @brief Строка со всеми разрешенными символами
  const string calc_chars = ".1234567890+-*/^()cosinexptal";
  /// @brief Строка с разрешенными мат. операциями
  const string math_oper_chars = "+-*/^";

  // проверка на количество скобочек
  if (count(func_str.begin(), func_str.end(), open_br) !=
      count(func_str.begin(), func_str.end(), closed_br))
    throw invalid_argument("brackets number mismatch");

  // первый и последний символы не должны быть знаками или точками
  // (кроме минуса спереди)
  if ((c_in_s(func_str[0], math_oper_chars + point) && func_str[0] != minus) ||
      c_in_s(func_str[func_str.size() - 1], math_oper_chars + point))
    throw invalid_argument("invalid syntax at edges");

  /// @brief Счетчик незакрытых скобочек
  int count_brackets = 0;

  // проходимся по всей строке
  for (size_t i = 0; i < func_str.size(); i++) {
    /// @brief Текущий символ
    char c = func_str[i];

    /// @brief Предыдущий символ
    char p_c = ' ';

    /// @brief Следующий символ
    char n_c = ' ';

    // (вычисление значений этих символов)
    if (i > 0) p_c = func_str[i - 1];
    if (i < (func_str.size() - 1)) n_c = func_str[i + 1];

    // проверка на отсутствие лишних символов
    if (!c_in_s(c, calc_chars)) {
      if (isalpha(c))
        throw invalid_argument("extra variable '" + string{c} + "'");
      else
        throw invalid_argument("unknown character '" + string{c} + "'");
    }

    // возле знака операции не должно быть других операций и точек,
    // а также открытой скобки слева или закрытой скобки справа
    // (минус на это мы не проверяем, так как он может быть унарный)
    if (c_in_s(c, math_oper_chars) && c != minus) {
      if ((c_in_s(p_c, math_oper_chars + point) ||
           c_in_s(n_c, math_oper_chars + point)) &&
          n_c != minus)  // но после знака минус стоять может
        throw invalid_argument("invalid syntax near sign");

      // минус не может стоять по обе стороны от знака
      else if (p_c == minus && n_c == minus)
        throw invalid_argument("invalid syntax near sign");

      // проверка на правильность скобок возле знака
      if (p_c == open_br || n_c == closed_br)
        throw invalid_argument("invalid brackets near sign");
    }

    // возле точки должны быть только числа
    if (c == point) {
      if ((!isdigit(p_c) || !isdigit(n_c)))
        throw invalid_argument("invalid syntax near point");
    }

    // считаем скобки
    else if (c == open_br) {
      count_brackets += 1;
      // и проверяем, что нету пустых
      if (n_c == closed_br) throw invalid_argument("empty brackets");
    } else if (c == closed_br) {
      count_brackets -= 1;
      // случай, когда после очередной закрытой скобки
      // - закрытых скобок оказывается больше
      if (count_brackets < 0) throw invalid_argument("extra bracket");
    }

    // возле числа должен стоять либо знак, либо точка, либо скобка
    // (при строке из одной цифры, эта проверка не подходит)
    else if (isdigit(c) && func_str.size() > 1) {
      /// @brief Строка с почти всеми символами, которые могут быть возле цифры
      // (почти, так как еще скобки с разных сторон, но мы их считаем далее)
      string valid_chars_near_digit = "0123456789" + math_oper_chars + point;

      /// @brief Левый (предыдущий) символ валиден
      // (у цифры слева может быть: цифра, точка, знак или открытая скобка)
      bool is_left_valid = 1;

      /// @brief Правый (следующий) символ валиден
      // (у цифры справа может быть: цифра, точка, знак или закрытая скобка)
      bool is_right_valid = 1;

      // (вычисление значений этих флагов)
      if (i == 0)
        is_right_valid = c_in_s(n_c, valid_chars_near_digit + closed_br);
      else if (i == func_str.size() - 1)
        is_left_valid = c_in_s(p_c, valid_chars_near_digit + open_br);
      else {
        is_right_valid = c_in_s(n_c, valid_chars_near_digit + closed_br);
        is_left_valid = c_in_s(p_c, valid_chars_near_digit + open_br);
      }

      // если хотя бы с одной стороны мы имеем не валидный символ
      if (!is_left_valid || !is_right_valid)
        throw invalid_argument("invalid syntax near digit");
    }
  }
}

void function::func_lexs_validation() const {
  /// @brief Вектор, со всеми разреш. лекс., обозначающими элем. мат. функции
  const vector<string> functions{"sin", "cos", "tan", "exp", "ln", "um"};

  for (size_t i = 0; i < lexs.size(); i++) {
    // string l = lexs[i];
    /// @brief Символ, обозначающий текущую лексему
    char l_c = s_to_c(lexs[i]);

    /// @brief Символ, обозначающий следующую лексему
    char n_c = ' ';

    // (вычисление этого символа)
    if (i < (lexs.size() - 1)) n_c = s_to_c(lexs[i + 1]);

    // FIXME: дальше какая-то дичь творится..

    // проверка использования постороннего имени
    if (isalpha(l_c) && !(is_double(lexs[i]))) {
      if (c_in_s(l_c, math_func_chars)) {
        size_t j = math_func_chars.find(l_c);
        if (lexs[i] != functions[j]) {
          if (lexs.size() > 1) {
            // если есть скобка, то это посторонняя элем. мат. функция
            if (lexs[i + 1] == "(")
              throw invalid_argument("invalid function name '" + lexs[i] + "'");
            else
              throw invalid_argument("extra variable '" + lexs[i] + "'");
          } else
            throw invalid_argument("extra variable '" + lexs[i] + "'");
        }
        // ситуации рода: tan | x + tan
        else if (l_c != uminus && (lexs.size() < 4 || i == lexs.size() - 1))
          throw invalid_argument("wrong function usage");

        // ситуация рода: x + tan + x
        else if (l_c != uminus && n_c != open_br)
          throw invalid_argument("wrong function usage");
      } else if (l_c != var_x)  // если имя начинается не с разрешенной буквы и
                                // не является x, то оно постороннее
        throw invalid_argument("extra variable '" + string{l_c} + "'");

      else if (l_c == var_x) {
        if (lexs.size() > 1 && i != lexs.size() - 1) {
          // если есть скобка, то это посторонняя элем. мат. функция
          // (ситуация рода: "x(x)")
          if (lexs[i + 1] == "(")
            throw invalid_argument("invalid function name '" + lexs[i] + "'");
        }
        // ситуация рода: "xx"
        if (lexs[i].size() > 1)
          throw invalid_argument("extra variable '" + lexs[i] + "'");
      }
    }
  }
}

}  // namespace Math_func