
#include "function.h"

// std libs
using std::string;
using std::vector;
#include <cmath>
#include <stack>
using std::stack;
#include <stdexcept>
using std::invalid_argument;

// utility
#include "../utility/utilities.h"
using namespace Backend_utilities;
using namespace Backend_consts;

namespace Math_func {

function::function(string _func_str)
    : func_str{spaces_deleted(_func_str)},
      lexs{lexemes()},
      rev_pol{reverse_polish()} {}

function::function(const function& func)
    : func_str{func.func_str}, lexs{func.lexs}, rev_pol{func.rev_pol} {}

function& function::operator=(const function& func) {
  if (this != &func) {
    func_str = func.func_str;
    lexs = func.lexs;
    rev_pol = func.rev_pol;
  }

  return *this;
}

bool function::has_var() const { return c_in_s('x', func_str); }

vector<string> function::lexemes() const {
  func_str_validation();

  vector<string> res;

  /// @brief Текущая лексема
  string lex;

  // TODO: написать комментарии по работе этого цикла

  for (size_t i = 0; i < func_str.size(); i++) {
    /// @brief Текущий символ строки
    char ch = func_str[i];
    switch (ch) {
      case minus: {
        if (lex.size() > 0) {
          res.push_back(lex);
          lex = "";
        }
        if (i == 0)
          res.push_back("um");
        else if (c_in_s(s_to_c(res[res.size() - 1]),
                        math_oper_chars + "(" + "u"))
          res.push_back("um");
        else
          res.push_back("-");
        break;
      }
      case open_br:
      case closed_br:
      case plus:
      case mul:
      case divi:
      case power: {
        if (lex.size() > 0) {
          res.push_back(lex);
          lex = "";
        }
        lex = ch;
        res.push_back(lex);
        lex = "";
        break;
      }
      case point:
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9': {
        if (lex.size() > 0 && !isdigit(lex[0])) {
          res.push_back(lex);
          lex = "";
        }
        lex += ch;
        break;
      }
      default: {
        if (!isblank(ch)) {
          if (lex.size() > 0 && isdigit(lex[0])) {
            res.push_back(lex);
            lex = "";
          }
          lex += ch;
        }
      }
    }
  }
  if (lex.size() > 0) res.push_back(lex);
  return (res);
}

vector<string> function::reverse_polish() const {
  func_lexs_validation();

  /// @brief Вектор, куда записывается итоговая обратная польская запись
  vector<string> res;

  /// @brief Стек с записанными операциями
  // (нужен для хранения операций в правильном порядке)
  stack<string> st_oper;
  st_oper.push("\0");

  for (const auto& lex : lexs) {
    /// @brief Символ, обозначающий текущую лексему
    // (нужен для switch-case)
    char l_c = s_to_c(lex);

    /// @brief Символ, обозначающий последний элемент в стеке с операциями
    char last = s_to_c(st_oper.top());

    // TODO: написать комментарии по работе этого свитча

    switch (l_c) {
      case number:
      case var_x: {
        res.push_back(lex);
        if (st_oper.size() > 0 && last == uminus) {
          res.push_back(st_oper.top());
          st_oper.pop();
        }
        break;
      }

      case power: {
        while (last == power || c_in_s(last, math_func_chars)) {
          res.push_back(st_oper.top());
          st_oper.pop();
          last = s_to_c(st_oper.top());
        }
        st_oper.push(lex);
        break;
      }

      case mul:
      case divi: {
        while (last == mul || last == divi || last == power ||
               c_in_s(last, math_func_chars)) {
          res.push_back(st_oper.top());
          st_oper.pop();
          last = s_to_c(st_oper.top());
        }
        st_oper.push(lex);
        break;
      }

      case plus:
      case minus: {
        while (c_in_s(last, math_oper_chars) || c_in_s(last, math_func_chars)) {
          res.push_back(st_oper.top());
          st_oper.pop();
          last = s_to_c(st_oper.top());
        }
        st_oper.push(lex);
        break;
      }

      case open_br: {
        st_oper.push(lex);
        break;
      }

      case closed_br: {
        while (true) {
          if (last == open_br) {
            st_oper.pop();
            break;
          } else {
            res.push_back(st_oper.top());
            st_oper.pop();
          }
          last = s_to_c(st_oper.top());
        }
        break;
      }
      case c_sin:
      case c_cos:
      case c_tan:
      case c_exp:
      case c_ln:
      case uminus: {
        st_oper.push(lex);
        break;
      }
      default: {
        throw std::runtime_error("Oops");
        break;
      }
    }
  }

  // перевод оставшихся в стеке знаков в обратную польскую запись
  while (st_oper.top() != "\0") {
    res.push_back(st_oper.top());
    st_oper.pop();
  }
  return res;
}

double function::calc(double x) const {
  /// @brief Стек, куда складываем уже посчитанные числа
  // IDK: а это точно так?
  stack<double> calced_numbs;

  // TODO: написать комментарии по работе этого цикла

  // раскрываем обратную польскую нотацию, подставляя x
  for (const auto& lex : rev_pol) {
    /// @brief Последний символ в стеке
    double l;

    /// @brief Предпоследний символ в стеке (последний после удаления l)
    double p;

    /// @brief Символ, обозначающий текущую лексему в обратной польской записи
    // (нужен для switch-case)
    char l_c = s_to_c(lex);

    if (c_in_s(l_c, math_func_chars)) {
      l = calced_numbs.top();  // запоминаем только последний
                               // (так как элем. мат. функции унарны)
      calced_numbs.pop();
      switch (l_c) {
        case c_sin:
          calced_numbs.push(sin(l));
          break;
        case c_cos:
          calced_numbs.push(cos(l));
          break;
        case c_tan:
          calced_numbs.push(tan(l));
          break;
        case c_exp:
          calced_numbs.push(exp(l));
          break;
        case c_ln:
          calced_numbs.push(log(l));
          break;
        case uminus:
          calced_numbs.push(-l);
          break;
      }
    } else if (c_in_s(l_c, math_oper_chars)) {
      l = calced_numbs.top();
      calced_numbs.pop();
      p = calced_numbs.top();  // также запоминаем предпоследний
                               // (так как мат. операции бинарны)
      calced_numbs.pop();
      switch (l_c) {
        case plus:
          calced_numbs.push(p + l);
          break;
        case minus:
          calced_numbs.push(p - l);
          break;
        case mul:
          calced_numbs.push(p * l);
          break;
        case divi:
          calced_numbs.push(p / l);
          break;
        case power:
          calced_numbs.push(pow(p, l));
          break;
      }
    } else {
      switch (l_c) {
        case number:
          calced_numbs.push(stod(lex));
          break;
        case var_x:
          calced_numbs.push(x);
          break;
        default:
          throw std::runtime_error("Oops");
          break;
      }
    }

    // получили математически недопустимое число
    if (std::isnan(calced_numbs.top()) || std::isinf(calced_numbs.top()))
      throw invalid_argument("violation of feasible region");
  }

  // последнее, что осталось в стеке после всех действий - и есть ответ
  return calced_numbs.top();
}

}  // namespace Math_func
