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

// MEANS: строка с разрешенными элементарным мат. функциями
const std::string math_func_chars = "sctelu";

// MEANS: строка с разрешенными мат. операциями
const std::string math_oper_chars = "+-*/^";

// MEANS: "сколь угодно малое" приращение x
constexpr double delta_x = 0.00001;

// MEANS: золотое сечение
const double phi = (1 + sqrt(5)) / 2;

// MEANS: максимальное кол-во проходов по поиску особой точки
constexpr unsigned int max_count = 10000;

}  // namespace Backend_consts