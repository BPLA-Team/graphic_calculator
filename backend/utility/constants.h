#pragma once

// std libs
#include <cmath>
#include <string>

namespace Backend_consts {

constexpr char point = '.';
constexpr char plus = '+';
constexpr char minus = '-';
constexpr char mul = '*';
constexpr char divi = '/';
constexpr char power = '^';
constexpr char open_br = '(';
constexpr char closed_br = ')';
constexpr char number = 'n';
constexpr char var_x = 'x';

constexpr char c_sin = 's';
constexpr char c_cos = 'c';
constexpr char c_tan = 't';
constexpr char c_exp = 'e';
constexpr char c_ln = 'l';
constexpr char uminus = 'u';

/// @brief Строка с разрешенными элементарным мат. функциями
const std::string math_func_chars = "sctelu";

/// @brief Строка с разрешенными мат. операциями
const std::string math_oper_chars = "+-*/^";

/// @brief "Сколь угодно малое" приращение x
constexpr double delta_x = 0.00001;

/// @brief Коэффициент золотого сечения
const double phi = (1 + sqrt(5)) / 2;

/// @brief Максимальное кол-во проходов по поиску особой точки
constexpr unsigned int max_count = 10000;

}  // namespace Backend_consts