#pragma once

// std libs
#include <string>

// Graph_lib
#include "../Graph_lib/Shapes.h"

namespace Graphix_calc {

// MEANS: фигура, представляющая собой мат. ось координат
class Axis : public Graph_lib::Shape {
 public:
  enum Orientation { horizontal, vertical };

  // ARGS: ориентация, центр коорд., длина оси, длина ед. отрезка, подпись
  Axis(Orientation orient, Graph_lib::Point origin, pix_amount length,
       double _unit_intr, const std::string& label_text);

  // ARGS: ориентация, центр коорд., длина оси, длина ед. отрезка,
  // ARGS: длина марк. отрезка, подпись
  Axis(Orientation orient, Graph_lib::Point origin, pix_amount length,
       double _unit_intr, pix_amount _mark_intr, const std::string& label_text);

  ~Axis();

  // methods

  // DOES: устанавливает все нужные точки
  // ARGS: ориентация, начало координат, длина оси
  void init(Orientation orient, Graph_lib::Point origin, pix_amount length);

  void draw_lines() const override;

  void set_color(Graph_lib::Color c);

  // ~methods

 private:
  // vars

  // MEANS: длина единичного отрезка
  double unit_intr;

  // MEANS: длина отмечаемого отрезка
  pix_amount mark_intr;

  // MEANS: надпись рядом с осью
  Graph_lib::Text label;

  // MEANS: насечки
  Graph_lib::Lines notches;

  // MEANS: надписи к насечкам
  std::vector<Graph_lib::Text*> marks;

  // ~vars
};

}  // namespace Graphix_calc