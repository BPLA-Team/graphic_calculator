#pragma once

// std libs
#include <string>
#include <vector>

// Graph_lib
#include "Point.h"
#include "fltk.h"

namespace Graph_lib {

class Shape;
class Widget;

class Window : public Fl_Window {
 public:
  using Fl_Window::resize;

  Window(pix_amount _width, pix_amount _height, const std::string& title);
  Window(Point top_left_corner, pix_amount _width, pix_amount _height,
         const std::string& title);

  virtual ~Window() = default;

  inline pix_amount w() const { return width; }

  inline pix_amount h() const { return height; }

  inline void resize(pix_amount _width, pix_amount _height) {
    width = _width;
    height = _height;
    size(_width, _height);
  }

  inline void set_label(const std::string& s) { label(s.c_str()); }

  void attach(Shape&);
  void attach(Widget&);

  // DOES: удаляет фигуру из соотв. списка
  // ARGS: фигура
  void detach(Shape&);
  // DOES: отвязывает виджет от окна, деактивируя коллбэки
  // ARGS: виджет
  void detach(Widget&);

  void put_on_top(Shape&);
  void put_on_top(Widget&);

 protected:
  void draw();

 private:
  std::vector<Shape*> shapes;
  pix_amount width;
  pix_amount height;

  virtual void init();
};

// DOES: вызывает основной цикл обработки событий библиотеки виджетов
inline int gui_main() { return Fl::run(); }

}  // namespace Graph_lib