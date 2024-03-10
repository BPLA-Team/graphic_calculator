#pragma once

// std libs
#include <string>

// Graphix_calc
#include "Numbed_button.h"

// Graph_lib
#include "../Graph_lib/Widgets.h"
#include "../Graph_lib/Window.h"

namespace Graphix_calc {

// MEANS: класс,с вводом мат. функции, кнопками для графиков, вывод (ошибок)
class Function_box : public Graph_lib::Widget {
 public:
  // упрощенный конструктор
  // ARGS: индекс текущего Function_box'а, callback-функции для:
  Function_box(unsigned long long int box_index,
               void cb_graphix_draw(void*, void*),
               void cb_graphix_hide(void*, void*),
               void cb_rem_func(void*, void*), void cb_deriv_draw(void*, void*),
               void cb_deriv_hide(void*, void*));

  // (по сути у Function_box нету пользовательского конструктора :)

  ~Function_box();

  // methods

  // DOES: привязывает все элементы к окну
  void attach(Graph_lib::Window&) override;

  // DOES: отвязывает все элементы от окна
  void detach(Graph_lib::Window&);

  // DOES: двигает все элементы
  void move(int dx, int dy) override;

  // input validation

  // DOES: устанавливает флаг о том, что мат. функция в поле ввода валидна
  inline void input_valid() { is_func_valid = true; }

  // DOES: устанавливает флаг о том, что мат. функция в поле ввода невалидна
  inline void input_invalid() { is_func_valid = false; }

  inline bool is_input_valid() const { return is_func_valid; };

  // graphix

  // DOES: устанавливает флаг о том, что график мат. функции нарисован
  inline void graphix_show() { is_graphix_visible = true; }

  // DOES: устанавливает флаг о том, что график мат. функции скрыт
  inline void graphix_hide() { is_graphix_visible = false; }

  inline bool is_graphix_hidden() const { return !is_graphix_visible; }

  // deriv

  // DOES: устанавливает флаг, что график производной мат. функции нарисован
  inline void deriv_show() { is_deriv_visible = true; }

  // DOES: устанавливает флаг о том, что график производной мат. функции скрыт
  inline void deriv_hide() { is_deriv_visible = false; }

  inline bool is_deriv_hidden() const { return !is_deriv_visible; }

  // setters

  // DOES: устанавливает индекс всем кнопкам и полям
  void set_index(unsigned long long);

  // DOES: устанавливает текст в поле вывода (ошибок)
  inline void set_message(const std::string& message) { out_box->put(message); }

  // DOES: устанавливает текст в поле вывода для производной мат. функции
  inline void set_deriv_message(const std::string& deriv_str) {
    out_der_box->put(deriv_str);
  }

  // getters

  // RETURNS: введенную мат. функцию
  inline std::string get_string() const { return in_box->get_string(); }

  // RETURNS: индекс текущего Function_box'а
  inline unsigned long long get_index() const {
    // (так как мы не храним этот индекс в качестве поля, берём от элемента)
    return draw_graphix_button->get_number();
  }

  // ~methods

 private:
  // vars

  // widgets

  // MEANS: кнопка для рисования графика мат. функции
  Numbed_button* draw_graphix_button;
  // MEANS: кнопка для скрытия графика мат. функции
  Numbed_button* hide_graphix_button;

  // MEANS: кнопка для рисования графика производной мат. функции
  Numbed_button* draw_deriv_button;
  // MEANS: кнопка для скрытия графика производной мат. функции
  Numbed_button* hide_deriv_button;
  // MEANS: поле для вывода текущей производной мат. функции
  Graph_lib::Out_box* out_der_box;

  // MEANS: поле для ввода мат. функции
  Graph_lib::In_box* in_box;
  // MEANS: поле для вывода ошибок по поводу введенной мат. функции
  Graph_lib::Out_box* out_box;

  // MEANS: кнопка для удаления текущего Function_box'а
  Numbed_button* rem_func_button;

  // flags

  // MEANS: флаг, сообщающий о валидности введенной мат. функции
  bool is_func_valid{false};

  // MEANS: флаг, сообщающий о видимости графика введенной мат. функции
  bool is_graphix_visible{false};

  // MEANS: флаг, сообщающий о видимости графика производной мат. функции
  bool is_deriv_visible{false};

  // ~vars
};

}  // namespace Graphix_calc