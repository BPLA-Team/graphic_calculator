#pragma once

// std libs
#include <functional>
#include <vector>

// Math_calc
#include "math_base.h"

namespace Math_calc {

/**
 * @brief Считает вещественные отрезки, где мат. функция определена
 * @details Деление на сегменты происходит на прямоуг. области, края - точки
 * @param calc: лямбда-выражение от мат. функции
 * @param left_bottom: левая нижняя точка - начало области деления на сегменты
 * @param right_top: правая верхняя точка - конец области деления на сегменты
 * @param precision: точность
 * @return std::vector<Segment>: вещественные отрезки
 */
std::vector<Segment> domain_segments(const std::function<double(double)>& calc,
                                     Math_calc::Point left_bottom,
                                     Math_calc::Point right_top,
                                     double precision);

}  // namespace Math_calc