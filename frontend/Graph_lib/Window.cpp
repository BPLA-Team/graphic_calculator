#include "Widgets.h"

namespace Graph_lib {

Window::Window(pix_amount _width, pix_amount _height, const std::string& title)
    : Fl_Window{int(_width), int(_height), title.c_str()},
      width{_width},
      height{_height} {
  init();
}

Window::Window(Point top_left_corner, pix_amount _width, pix_amount _height,
               const std::string& title)
    : Fl_Window{int(top_left_corner.x), int(top_left_corner.y), int(_width),
                int(_height), title.c_str()},
      width{_width},
      height{_height} {
  init();
}

void Window::init() {
  Fl_Group::resizable(this);
  Fl_Window::show();
}

void Window::draw() {
  Fl_Window::draw();
  for (unsigned int i = 0; i < shapes.size(); ++i) shapes[i]->draw();
}

void Window::attach(Widget& widget) {
  Fl_Group::begin();  // FTLK: начинаем прикреплять к этому окну новые
                      // Fl_Widgets
  widget.attach(*this);  // позволяем виджету создать свои Fl_Widgets
  Fl_Group::end();  // FTLK: прекращаем прикреплять новые
                    // Fl_Widgets к этому окну
}

void Window::detach(Widget& widget) { widget.hide(); }

void Window::attach(Shape& shape) { shapes.push_back(&shape); }

void Window::detach(Shape& shape) {
  // последнее прикрепленное будет выпущено первым
  for (unsigned int i = shapes.size(); 0 < i; --i)
    if (shapes[i - 1] == &shape) shapes.erase(shapes.begin() + (i - 1));
}

void Window::put_on_top(Shape& shape) {
  detach(shape);
  attach(shape);
}

void Window::put_on_top(Widget& widget) {
  detach(widget);
  attach(widget);
}

}  // namespace Graph_lib
