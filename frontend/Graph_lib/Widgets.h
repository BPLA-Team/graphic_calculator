#pragma once

// std libs
#include <stdexcept>

// Graph_lib
#include "Shapes.h"
#include "Window.h"

namespace Graph_lib {

using Callback = void (*)(
    void*, void*);  // Обязательный тип функции FLTK для всех обратных вызовов

template <class W>
W& reference_to(void* ptr_wid) {
  return *static_cast<W*>(ptr_wid);
}

/**
 * @brief Абстрактный объект взаимодействия с пользователем
 * @details Виджет — это дескриптор Fl_widget, но *не* Fl_widget, мы стараемся
 * держать классы интерфейса на расстоянии от FLTK)
 */
class Widget {
 public:
  Widget() = default;

  inline Widget(Point _loc, pix_amount _width, pix_amount _height,
                const std::string& _label, Callback _cb)
      : loc{_loc}, width{_width}, height{_height}, label{_label}, cb{_cb} {}

  Widget(const Widget&) = delete;  // (предотвращение копирования)

  virtual ~Widget() = default;

  // methods

  virtual void move(int dx, int dy);

  inline virtual void hide() { ptr_wid->hide(); }

  inline virtual void show() { ptr_wid->show(); }

  virtual void attach(Window&) = 0;  // (определяется наследниками)

  Window& window() { return *own; }

  Widget& operator=(const Widget&) = delete;  // (предотвращение копирования)

  // ~methods

 protected:
  // vars

  /// @brief Окно, которому принадлежит виджет
  Window* own;

  /// @brief Указатель на FLTK виджет
  Fl_Widget* ptr_wid;

  Point loc;
  pix_amount width;
  pix_amount height;

  std::string label;
  Callback cb;

  // ~vars
};

//-------------------------------------------------------------------------------------------------------------------------------

struct Button : Widget {
  inline Button(Point _loc, pix_amount _width, pix_amount _height,
                const std::string& _label, Callback _cb)
      : Widget{_loc, _width, _height, _label, _cb} {}

  // methods

  void attach(Window&);

  // ~methods
};

//-------------------------------------------------------------------------------------------------------------------------------

struct In_box : Widget {
  inline In_box(Point _loc, pix_amount _width, pix_amount _height,
                const std::string& s)
      : Widget{_loc, _width, _height, s, nullptr} {}

  // methods

  std::string get_string();

  void attach(Window& win);

  // ~methods
};

//-------------------------------------------------------------------------------------------------------------------------------

struct Out_box : Widget {
  inline Out_box(Point _loc, pix_amount _width, pix_amount _height,
                 const std::string& s)
      : Widget{_loc, _width, _height, s, nullptr} {}

  // methods

  void put(const std::string&);

  void attach(Window& win);

  // ~methods
};

}  // namespace Graph_lib
