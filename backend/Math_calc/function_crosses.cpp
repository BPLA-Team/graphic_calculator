#include "function_crosses.h"

// std libs
using std::pair;
using std::string;
using std::vector;

// Math_calc
#include "domain_segments.h"

// utility
#include "../utility/utilities.h"
using Backend_utilities::absolute;

namespace Math_calc {

function_crosses::function_crosses(
    std::pair<Math_func::function, Math_func::function> funcs,
    Point left_bottom, Point right_top, double _precision)
    // рассматриваем иксы пересечения мат. функций, как точки-корни для мат. функции - их разницы
    : function_roots{Math_func::function{funcs.first.get_func_str() + "-(" +
                                         funcs.second.get_func_str() + ")"},
                     left_bottom, right_top, _precision},
      precision{_precision},
      f{funcs.first},
      points{crosses(left_bottom, right_top)} {}

vector<Point> function_crosses::crosses(Point left_bottom,
                                        Point right_top) const {
  vector<Point> res;
  for (const auto& seg :
       domain_segments(f.calculate, left_bottom, right_top, precision)) {
    for (const auto& local_seg : estimated_segment(seg)) {
      double x = function_roots::root_on_interval(local_seg);
      double y = f(x);
      // отличие от нахождения корней заключается в том, что теперь нам не нужна проверка на
      // приближенность нулю
      res.push_back(Point{x, y});
    }
  }
  return res;
}

}  // namespace Math_calc