#pragma once

// std libs
#include <functional>
#include <vector>

// Math_calc
#include "math_base.h"

namespace Math_calc {

// RETURNS: вещественные отрезки, где мат. функция определена
// ARGS: лямбда-выражение от мат. функции,
// ARGS: левая нижняя точка - начало области деления на сегменты,
// ARGS: правая верхняя точка - конец области деления на сегменты, точность
// (деление на сегменты происходит на прямоуг. области, края которой - точки)
std::vector<Segment> domain_segments(const std::function<double(double)>& calc,
                                     Math_calc::Point left_bottom,
                                     Math_calc::Point right_top,
                                     double precision);

}  // namespace Math_calc