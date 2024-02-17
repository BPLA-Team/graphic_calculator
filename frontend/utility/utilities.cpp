#include "utilities.h"

// std libs
#include <iomanip>
using namespace std;

namespace Frontend_utilities {

string format(double num, unsigned int after_comma_digits_amount) {
  // (этот код написал ChatGPT)
  //// сори Илюх, но так более практично

  // устанавливаем точность кол-ва цифр после запятой
  ostringstream oss;
  oss << fixed << setprecision(after_comma_digits_amount) << num;
  string formatted = oss.str();

  // удаляем незначащие нули после точки
  size_t found = formatted.find_last_not_of('0');
  if (formatted[found] == '.')
    found--;  // если последний символ после нулей - точка, убираем ее тоже
  formatted = formatted.substr(0, found + 1);

  return formatted;
}

Graph_lib::Point converted_to_pix(Math_calc::Point p, Graph_lib::Point origin,
                                  double unit_intr) {
  return {origin.x + pix_amount(p.x * unit_intr),
          origin.y - pix_amount(p.y * unit_intr)};
}

Math_calc::Point converted_to_real(Graph_lib::Point p, Graph_lib::Point origin,
                                   double unit_intr) {
  return {(double(p.x) - double(origin.x)) / unit_intr,
          (-double(p.y) + double(origin.y)) / unit_intr};
}

}  // namespace Frontend_utilities