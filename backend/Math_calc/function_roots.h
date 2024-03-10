#pragma once

// std libs
#include <string>
#include <vector>

// Math_calc
#include "math_base.h"

// Math_func
#include "../Math_func/function.h"

namespace Math_calc {

// MEANS: класс, хранящий в себе точки - пересеч. графика мат. функ. с осью Ox
class function_roots {
 public:
  function_roots() = default;

  // ARGS: мат. функция, левая нижняя точка - начало области поиска точек,
  // ARGS: правая верхняя точка - конец области поиска точек, точность
  // (поиск точек происходит на прямоугольной области, края которой - точки)
  function_roots(Math_func::function _func, Math_calc::Point left_bottom,
                 Math_calc::Point right_top, double _precision);

  // methods

  // (перегрузка явного преобразования типов)
  inline explicit operator std::vector<Math_calc::Point>() const {
    return points;
  }

  // ~methods

 protected:
  // methods

  // RETURNS: подсегменты, где могут находиться корни
  // ARGS: сегмент, на котором ищем
  // (используя тот факт, что по разные стороны от точки-корня мат. функция
  // имеет разные знаки)
  std::vector<Segment> estimated_segment(Segment) const;

  // RETURNS: корень на интервале (значение x)
  // ARGS: сегмент, на котором ищем
  // (используя метод золотого сечения)
  double root_on_interval(Segment) const;

  // ~methods

 private:
  // vars

  // MEANS: точность (используем везде, поэтому сохраняем в качестве поля)
  double precision;

  // MEANS: введенная мат. функция
  Math_func::function f;

  std::vector<Point> points;

  // ~vars

  // methods

  // RETURNS: все корни (точки: пары вида (x,y))
  // ARGS: левая нижняя точка - начало области поиска точек,
  // ARGS: правая верхняя точка - конец области поиска точек
  std::vector<Point> roots(Math_calc::Point left_bottom, Point right_top) const;

  // ~methods
};

}  // namespace Math_calc