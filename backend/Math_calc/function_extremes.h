#pragma once

// std libs
#include <string>
#include <vector>

// Math_calc
#include "function_roots.h"
#include "math_base.h"

namespace Math_calc {

// MEANS: класс, хранящий в себе вектор точек - лок. экстремумы мат. функции
class function_extremes : public function_roots {
 public:
  // ARGS: мат. функция, левая нижняя точка - начало области поиска точек,
  // ARGS: правая верхняя точка - конец области поиска точек, точность
  // (поиск точек происходит на прямоугольной области, краями которой - точки)
  function_extremes(Math_func::function _func, Math_calc::Point left_bottom,
                    Math_calc::Point right_top, double _precision);

  // methods

  // (перегрузка явного преобразования типов)
  inline explicit operator std::vector<Math_calc::Point>() const {
    return points;
  }

  // ~methods

 private:
  enum ExtremeType { pnt_min, pnt_max };

  // vars

  // MEANS: точность
  // (используем везде, поэтому сохраняем в качестве поля)
  double precision;

  // MEANS: введенная мат. функция
  Math_func::function f;

  std::vector<Point> points;

  // ~vars

  // methods

  // RETURNS: подсегменты, где могут находиться экстремумы
  // ARGS: тип экстремума, сегмент, на котором ищем
  std::vector<Segment> estimated_segment(ExtremeType, Segment) const;

  // RETURNS: экстремум на интервале (значение x)
  // ARGS: тип экстремума, сегмент, на котором ищем
  // (используя метод золотого сечения)
  double extreme_on_interval(ExtremeType, Segment) const;

  // RETURNS: все локальные экстремумы (точки: пары вида (x,y))
  // ARGS: левая нижняя точка - начало области поиска точек,
  // ARGS: правая верхняя точка - конец области поиска точек
  std::vector<Point> extremes(Math_calc::Point left_bottom,
                              Point right_top) const;

  // ~methods
};

}  // namespace Math_calc