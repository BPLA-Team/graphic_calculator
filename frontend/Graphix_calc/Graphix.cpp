#include "Graphix.h"

// std libs
#include <stdexcept>
using std::function;
using std::invalid_argument;

// utility
#include "../utility/utilities.h"
using namespace Frontend_utilities;

namespace Graphix_calc {

Graphix::Graphix(function<double(double)> calc, double min_x, double max_x,
                 Graph_lib::Point origin, unsigned int point_amount,
                 double unit_intr) {
  if (max_x - min_x <= 0) invalid_argument("bad graphing range");

  if (point_amount < 2) invalid_argument("graphing point_amount must be >= 2");

  // (в том случае, если график - простая линия)
  else if (point_amount == 2) {
    add(converted_to_pix({min_x, calc(min_x)}, origin, unit_intr));
    add(converted_to_pix({max_x, calc(max_x)}, origin, unit_intr));
  } else {
    /// @brief Перебираемое значение x мат. функции
    double x = min_x;
    // (цикл нужен только, чтобы считать сколько точек уже было добавлено)
    for (unsigned int i = 0; i < point_amount; i++) {
      add(converted_to_pix({x, calc(x)}, origin, unit_intr));
      x += (max_x - min_x) / double(point_amount);
    }
  }
}

}  // namespace Graphix_calc
