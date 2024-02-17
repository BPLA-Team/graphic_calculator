#include "Bothput_box.h"

// std libs
using std::string;

// Graph_lib
using Graph_lib::Point;
using Graph_lib::reference_to;

namespace Graphix_calc {

Bothput_box::Bothput_box(Point _loc, pix_amount _width, pix_amount _height,
                         const std::string& s)
    : Graph_lib::Widget(_loc, _width, _height, s, nullptr) {}

void Bothput_box::attach(Graph_lib::Window& win) {
  // (везде преобразования, так как внутри FLTK пиксели - int'ы)
  ptr_wid = new Fl_Input{int(loc.x), int(loc.y), int(width), int(height),
                         label.c_str()};
  own = &win;
}

string Bothput_box::get_string() const {
  Fl_Input& ptr_input = reference_to<Fl_Input>(ptr_wid);
  return string(ptr_input.value());
}

void Bothput_box::put_string(const std::string& s) {
  reference_to<Fl_Output>(ptr_wid).value(s.c_str());
}

}  // namespace Graphix_calc