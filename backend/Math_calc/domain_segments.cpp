#include "domain_segments.h"

// std libs
using std::function;
using std::vector;

namespace Math_calc {

vector<Segment> domain_segments(const function<double(double)>& calc,
                                Math_calc::Point left_bottom,
                                Math_calc::Point right_top, double precision) {
  double max_x = right_top.x;
  double max_y = right_top.y * 2;  // для большей точности
  double min_x = left_bottom.x;
  double min_y = left_bottom.y * 2;  // для большей точности

  std::vector<Segment> res;

  /// @brief Начало отрезка уже было записано
  bool is_x_started = false;

  /// @brief Текущий отрезок
  Segment seg;

  for (double x = min_x; x < max_x; x += precision) {
    if (!is_x_started) {
      // если мы еще не записали начало отрезка, проверяем на то, что значение
      // не нарушает ОДЗ и не больше максимально допустимой высоты
      try {
        double y = calc(x);
        if ((y > min_y) && (y < max_y)) {
          seg.start = x;
          is_x_started = true;
        }
      } catch (...) {
        // в случае возникновение какой-либо ошибки, игнорируем эту точку, так
        // как значение на ней нам точно не подходит
      }
    } else {
      try {
        double y = calc(x);
        // в случае, если значение мат. функции превысило допустимое - обрезаем
        // отрезок предыдущим значением
        if ((y > max_y) || (y < min_y)) {
          seg.end = x - precision;
          is_x_started = false;
          if (seg.start < seg.end) res.push_back(seg);
          seg = Segment();
        }
      } catch (...) {
        // в этом случае также обрезаем отрезок предыдущим значением, так как на
        // текущем мы получили ошибку
        seg.end = x - precision;
        is_x_started = false;
        if (seg.start < seg.end) res.push_back(seg);
        seg = Segment();
      }
    }
  }

  // если в самом конце не успели закрыть отрезок, делаем это правой границей
  // (скорее всего, мы её просто перескочили или дошли до max_x - precision)
  if (is_x_started) {
    seg.end = max_x;
    if (seg.start < seg.end) res.push_back(seg);
  }

  // (этот кусок может пригодится для поиска нужных формул точности)
  // for (const auto& i : res)
  //     cout << "{" << i.start << ", " << i.end << "}, ";
  // cout << endl;

  return res;
}

}  // namespace Math_calc