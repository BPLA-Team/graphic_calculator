// std libs
#include <string>

// Graph_lib
#include "../Graph_lib/Point.h"

// Backend
#include "../../backend.h"

namespace Frontend_utilities {

/**
 * @param num: веществ. число
 * @param after_comma_digits_amount: кол-во знаков после точки
 * @return std::string: отформатированная строка
 */
std::string format(double num, unsigned int after_comma_digits_amount = 2);

Graph_lib::Point converted_to_pix(Math_calc::Point p, Graph_lib::Point origin,
                                  double unit_intr);

Math_calc::Point converted_to_real(Graph_lib::Point p, Graph_lib::Point origin,
                                   double unit_intr);

}  // namespace Frontend_utilities