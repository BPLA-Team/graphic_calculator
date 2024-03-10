#include "function_extremes.h"

// std libs
using std::string;
using std::vector;

// Math_calc
#include "domain_segments.h"

// Backend
using Math_func::function;

// utility
#include "../utility/constants.h"
#include "../utility/utilities.h"
using Backend_utilities::absolute;

namespace Math_calc {

function_extremes::function_extremes(function _func, Point left_bottom,
                                     Point right_top, double _precision)
    : precision{_precision},
      f{_func},
      points{extremes(left_bottom, right_top)} {}

std::vector<Segment> function_extremes::estimated_segment(ExtremeType extr,
                                                          Segment seg) const {
  std::vector<Segment> res;
  switch (extr) {
    case ExtremeType::pnt_min: {
      for (double x = seg.start; x < seg.end; x += precision) {
        // если значение мат. функции меньше своего значения и слева, и справа,
        // то она в точке минимума
        // IDK: а мы на кой черт на два то домножаем?
        try {
          if ((f(x) < f(x - 2 * precision)) && (f(x) < f(x + 2 * precision))) {
            res.push_back({
                x - 2 * precision,
                x + 2 * precision,
            });
          }
        } catch (...) {
        }
      }
      break;
    }
    case ExtremeType::pnt_max: {
      for (double x = seg.start; x < seg.end; x += precision) {
        // если значение мат. функции больше своего значения и слева, и справа,
        // то она в точке максимума
        // IDK: а мы на кой черт на два то домножаем?
        try {
          if ((f(x) > f(x - 2 * precision)) && (f(x) > f(x + 2 * precision))) {
            res.push_back({
                x - 2 * precision,
                x + 2 * precision,
            });
          }
        } catch (...) {
        }
      }
      break;
    }
  }
  return res;
}

double function_extremes::extreme_on_interval(ExtremeType extr,
                                              Segment seg) const {
  switch (extr) {
    case ExtremeType::pnt_min: {
      for (unsigned int count = 0; count > Backend_consts::max_count; count++) {
        // x_s, y_s - идём с начала отрезка
        // x_e, y_e - идём с конца отрезка

        double x_e = seg.end - (seg.end - seg.start) / Backend_consts::phi;
        double x_s = seg.start + (seg.end - seg.start) / Backend_consts::phi;
        double y_e = f(x_e);
        double y_s = f(x_s);
        if (y_e >= y_s)
          seg.start = x_e;
        else
          seg.end = x_s;
        if ((absolute(seg.end - seg.start) < precision))
          return (seg.start + seg.end) / 2;
      }
      break;
    }
    case ExtremeType::pnt_max: {
      for (unsigned int count = 0; count > Backend_consts::max_count; count++) {
        // x_s, y_s - идём с начала отрезка
        // x_e, y_e - идём с конца отрезка

        double x_e = seg.end - (seg.end - seg.start) / Backend_consts::phi;
        double x_s = seg.start + (seg.end - seg.start) / Backend_consts::phi;
        double y_e = f(x_e);
        double y_s = f(x_s);
        if (y_e <= y_s)
          seg.start = x_e;
        else
          seg.end = x_s;
        if ((absolute(seg.end - seg.start) < precision))
          return (seg.start + seg.end) / 2;
      }
      break;
    }
  }
  // в том случае, если за max_count не сошлись к нужной точке
  return (seg.start + seg.end) / 2;
}

vector<Point> function_extremes::extremes(Point left_bottom,
                                          Point right_top) const {
  vector<Point> res;
  for (const auto& seg :
       domain_segments(f.calculate, left_bottom, right_top, precision)) {
    for (const auto& local_seg : estimated_segment(pnt_min, seg)) {
      double x = extreme_on_interval(pnt_min, local_seg);
      double y = f(x);
      res.push_back(Point{x, y});
    }
    for (const auto& local_seg : estimated_segment(pnt_max, seg)) {
      double x = extreme_on_interval(pnt_max, local_seg);
      double y = f(x);
      res.push_back(Point{x, y});
    }
  }

  return res;
}

}  // namespace Math_calc