#pragma once

// std libs
#include <functional>
#include <vector>

// Graph_lib
#include "../Graph_lib/Shapes.h"

namespace Graphix_calc {

/// @brief Фигура, представляющая собой график мат. функции
class Graphix : public Graph_lib::Shape {
 public:
  /**
   * @brief Инициализирует новый экземпляр Graphix (область определения
   * [min_x:max_x))
   * @param calc: лямбда-выр. от мат. функции
   * @param min_x: мин. знач. x
   * @param max_x: макс. знач. x
   * @param origin: начало координат
   * @param point_amount: кол-во точек
   * @param unit_intr: единичный отрезок
   */
  Graphix(std::function<double(double)> calc, double min_x, double max_x,
          Graph_lib::Point origin, unsigned int point_amount, double unit_intr);
};

}  // namespace Graphix_calc
