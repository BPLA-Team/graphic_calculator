#pragma once

// std libs
#include <string>
#include <utility>
#include <vector>

// Math_calc
#include "function_roots.h"
#include "math_base.h"

namespace Math_calc {

// MEANS: класс, хранящий в себе вектор точек - пересечений двух мат. функций
class function_crosses : public function_roots {
 public:
  // ARGS: пара мат. функций, левая нижняя точка - начало области поиска точек,
  // ARGS: правая верхняя точка - конец области поиска точек, точность
  // (поиск точек происходит на прямоугольной области, края которой - точки)
  function_crosses(std::pair<Math_func::function, Math_func::function> funcs,
                   Math_calc::Point left_bottom, Math_calc::Point right_top,
                   double _precision);

  // methods

  // (перегрузка явного преобразования типов)
  inline explicit operator std::vector<Math_calc::Point>() const {
    return points;
  }

  // ~methods

 private:
  // vars

  // MEANS: точность
  // (используем везде, поэтому сохраняем в качестве поля)
  double precision;

  // MEANS: одна из введенных мат. функций
  // (одна, так как нужно просто найти y, можно и в одну подставить)
  Math_func::function f;

  std::vector<Point> points;

  // ~vars

  // methods

  // RETURNS: все пересечения двух мат. функций (точки: пары вида (x,y))
  // ARGS: левая нижняя точка - начало области поиска точек,
  // ARGS: правая верхняя точка - конец области поиска точек
  std::vector<Point> crosses(Math_calc::Point left_bottom, Point right_top)
      const;  // (чтобы не хранить границы внутри класса - в аргументы)

  // ~methods
};

}  // namespace Math_calc