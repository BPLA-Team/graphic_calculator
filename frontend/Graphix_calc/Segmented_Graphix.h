#pragma once

// std libs
#include <functional>
#include <string>

// Graph_lib
#include "../Graph_lib/Shapes.h"

// Graphix_calc
#include "Graphix.h"

// Backend
#include "../../backend.h"

namespace Graphix_calc {

// MEANS: фигура, представляющая собой график мат. функции, поделенный на сегменты, связанные с ОДЗ
class Segmented_graphix : public Graph_lib::Shape {
 public:
  Segmented_graphix() = default;

  // ARGS: лямбда-выражение от мат. функции, длина ед. отрезка, начало координат
  // ARGS: левая нижняя точка - начало области деления на сегменты,
  // ARGS: правая верхняя точка - конец области деления на сегменты
  // (деление на сегменты происходит на прямоугольной области, краями которой и являются точки)
  Segmented_graphix(std::function<double(double)> _calc, double unit_intr,
                    Graph_lib::Point origin, Graph_lib::Point left_bottom,
                    Graph_lib::Point right_top);

  // ARGS: указатель на график простой мат. функции
  Segmented_graphix(Graphix_calc::Graphix* graphix);

  ~Segmented_graphix();

  // methods

  void set_color(Graph_lib::Color c);

  inline Segmented_graphix& operator=(Graphix_calc::Graphix* graphix) {
    seged_graphix = std::vector<Graphix_calc::Graphix*>{graphix};
    return *this;
  }

  // ~methods

 private:
  // vars

  // MEANS: лямбда-выражение от мат. функции
  std::function<double(double)> calc;

  // MEANS: вещественные отрезки, где мат. функция определена
  std::vector<Math_calc::Segment> segs;

  // MEANS: график мат. функции, поделенный на сегменты, связанные с ОДЗ
  std::vector<Graphix_calc::Graphix*> seged_graphix;

  // ~vars

  // methods

  void draw_lines() const override;

  // RETURNS: вещественные отрезки, где мат. функция определена
  // ARGS: длина ед. отрезка, начало координат
  // ARGS: левая нижняя точка - начало области деления на сегменты,
  // ARGS: правая верхняя точка - конец области деления на сегменты
  // (именно здесь вызывается бэкендовская domain_segments)
  std::vector<Math_calc::Segment> segments(double unit_intr,
                                           Graph_lib::Point origin,
                                           Graph_lib::Point left_bottom,
                                           Graph_lib::Point right_top) const;

  // RETURNS: график мат. функции, поделенный на сегменты, связанные с ОДЗ
  // ARGS: длина ед. отрезка, начало координат
  // ARGS: левая нижняя точка - начало области деления на сегменты,
  // ARGS: правая верхняя точка - конец области деления на сегменты
  std::vector<Graphix_calc::Graphix*> segmented_graphix(
      double unit_intr, Graph_lib::Point origin, Graph_lib::Point left_bottom,
      Graph_lib::Point right_top) const;

  // ~methods
};

}  // namespace Graphix_calc