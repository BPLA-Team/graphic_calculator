#include "Widgets.h"

// std libs
#include <sstream>
#include <string>

namespace Graph_lib {

void Widget::move(int dx, int dy) {
  if (dx + int(loc.x) < 0 || dy + int(loc.y) < 0)
    throw std::invalid_argument("bad dx or dy");

  hide();
  ptr_wid->position(loc.x += dx, loc.y += dy);
  show();
}

//-------------------------------------------------------------------------------------------------------------------------------

void Button::attach(Window& win) {
  // (FLTK работает на int'ах, так что преобразуем)
  ptr_wid = new Fl_Button{int(loc.x), int(loc.y), int(width), int(height),
                          label.c_str()};
  // (великий и ужасный...)
  ptr_wid->callback(reinterpret_cast<Fl_Callback*>(cb), this);
  own = &win;
}

//-------------------------------------------------------------------------------------------------------------------------------

std::string In_box::get_string() {
  Fl_Input& pi = reference_to<Fl_Input>(ptr_wid);
  return std::string(pi.value());
}

void In_box::attach(Window& win) {
  // (FLTK работает на int'ах, так что преобразуем)
  ptr_wid = new Fl_Input{int(loc.x), int(loc.y), int(width), int(height),
                         label.c_str()};
  own = &win;
}

//-------------------------------------------------------------------------------------------------------------------------------

void Out_box::put(const std::string& s) {
  reference_to<Fl_Output>(ptr_wid).value(s.c_str());
}

void Out_box::attach(Window& win) {
  // (FLTK работает на int'ах, так что преобразуем)
  ptr_wid = new Fl_Output{int(loc.x), int(loc.y), int(width), int(height),
                          label.c_str()};
  own = &win;
}

}  // namespace Graph_lib
