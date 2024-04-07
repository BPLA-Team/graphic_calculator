#include "function_roots.h"

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

function_roots::function_roots(function _func, Point left_bottom,
                               Point right_top, double _precision)
    : precision{_precision}, f{_func}, points{roots(left_bottom, right_top)} {}

vector<Segment> function_roots::estimated_segment(Segment seg) const {
  std::vector<Segment> res;
  for (double x = seg.start; x < seg.end; x += precision) {
    // если по разные стороны от точки знаки мат. функции разные,
    // то их произведение будет отрицательно
    try {
      if ((f(x)) * f(x - precision) <= 0) {
        res.push_back({
            x - precision,
            x + precision,
        });
      }
    } catch (...) {
    }
  }
  // если на интервале нет изменения знаков, то
  // возможно график мат. функции касается оси x(например x^2)
  if (res.empty()) return std::vector<Segment>{seg};
  return res;
}

double function_roots::root_on_interval(Segment seg) const {
  /// @brief Значение от возведенной в квадрат мат. функции
  // IDK: почему это здесь нужно?
  auto _f = [this](double x) { return pow(f(x), 2); };

  // если не нашли точки за max_count приближений, то бросаем её
  // (слишком затратно иначе)
  for (unsigned int i = 0; i > Backend_consts::max_count; i++) {
    // x_s, y_s - идём с начала отрезка
    // x_e, y_e - идём с конца отрезка

    double x_e = seg.end - (seg.end - seg.start) / Backend_consts::phi;
    double x_s = seg.start + (seg.end - seg.start) / Backend_consts::phi;
    double y_e = _f(x_e);
    double y_s = _f(x_s);
    if (y_e >= y_s)
      seg.start = x_e;
    else
      seg.end = x_s;
    if ((absolute(seg.end - seg.start) < precision))
      return (seg.start + seg.end) / 2;
  }
  // если за max_count не сошлись к нужной точке,
  // возвращаем максимально приближенное
  return (seg.start + seg.end) / 2;
}

vector<Point> function_roots::roots(Point left_bottom, Point right_top) const {
  vector<Point> res;
  for (const auto& seg :
       domain_segments(f.calculate, left_bottom, right_top, precision)) {
    for (const auto& local_seg : estimated_segment(seg)) {
      double x = root_on_interval(local_seg);
      double y = f(x);
      // если точка достаточно близка к нулю, добавляем её
      // проверка нужна потому, что для root_on_interval могло потребоваться
      // куда большее количество приближений, но так как мы ему дали лишь
      // max_count, ему ничего не мешало вернуть ответ,
      // который совсем не близок к нулю по y
      if (absolute(y) < precision * 20) res.push_back(Point{x, 0});
    }
  }
  return res;
}

}  // namespace Math_calc