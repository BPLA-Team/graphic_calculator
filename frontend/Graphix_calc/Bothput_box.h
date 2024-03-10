#pragma once

// std libs
#include <string>

// Graph_lib
#include "../Graph_lib/Point.h"
#include "../Graph_lib/Widgets.h"
#include "../Graph_lib/Window.h"

namespace Graphix_calc {

// MEANS: класс поля, которое представляем собой и ввод и вывод
class Bothput_box : public Graph_lib::Widget {
 public:
  Bothput_box(Graph_lib::Point _loc, pix_amount _width, pix_amount _height,
              const std::string& s);

  // methods

  void attach(Graph_lib::Window& win);

  std::string get_string() const;

  void put_string(const std::string&);

  // ~methods
};

}  // namespace Graphix_calc