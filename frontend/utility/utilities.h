// std libs
#include <string>

// Graph_lib
#include "../Graph_lib/Point.h"

// Backend
#include "../../backend.h"

namespace Frontend_utilities {

// RETURNS: отформатированная строка
// ARGS: веществ. число, кол-во знаков после точки
std::string format(double num, unsigned int after_comma_digits_amount = 2);

// RETURNS: пиксельная точка
// ARGS: веществ. точка, начало координат, ед. отрезок
Graph_lib::Point converted_to_pix(Math_calc::Point p, Graph_lib::Point origin,
                                  double unit_intr);

// RETURNS: веществ. точка
// ARGS: пиксельная точка, начало координат, ед. отрезок
Math_calc::Point converted_to_real(Graph_lib::Point p, Graph_lib::Point origin,
                                   double unit_intr);

}  // namespace Frontend_utilities