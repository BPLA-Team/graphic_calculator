#pragma once

// std libs
#include <functional>
#include <vector>

// Graph_lib
#include "../Graph_lib/Shapes.h"

namespace Graphix_calc {

// MEANS: фигура, представляющая собой график мат. функции
class Graphix : public Graph_lib::Shape {
 public:
  // ARGS: лямбда-выр. от мат. функции, мин. знач. x, макс. знач. x,
  // (область определения [min_x:max_x))
  // ARGS: начало координат, кол-во точек, единичный отрезок
  Graphix(std::function<double(double)> calc, double min_x, double max_x,
          Graph_lib::Point origin, unsigned int point_amount, double unit_intr);
};

}  // namespace Graphix_calc
