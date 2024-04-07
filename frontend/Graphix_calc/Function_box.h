#pragma once

// std libs
#include <string>

// Graphix_calc
#include "Numbed_button.h"

// Graph_lib
#include "../Graph_lib/Widgets.h"
#include "../Graph_lib/Window.h"

namespace Graphix_calc {

/// @brief Класс с вводом мат. функции, кнопками для графиков, вывод ошибок
class Function_box : public Graph_lib::Widget {
 public:
  /// @brief Упрощенный конструктор
  Function_box(unsigned long long int box_index,
               void cb_graphix_draw(void*, void*),
               void cb_graphix_hide(void*, void*),
               void cb_rem_func(void*, void*), void cb_deriv_draw(void*, void*),
               void cb_deriv_hide(void*, void*));

  // (по сути у Function_box нету пользовательского конструктора :)

  ~Function_box();

  // methods

  /// @brief Привязывает все элементы к окну
  void attach(Graph_lib::Window&) override;

  /// @brief Отвязывает все элементы от окна
  void detach(Graph_lib::Window&);

  /**
   * @brief Двигает все элементы
   * @param dx
   * @param dy
   */
  void move(int dx, int dy) override;

  // input validation

  /// @brief Устанавливает флаг о том, что мат. функция в поле ввода валидна
  inline void input_valid() { is_func_valid = true; }

  /// @brief Устанавливает флаг о том, что мат. функция в поле ввода невалидна
  inline void input_invalid() { is_func_valid = false; }

  inline bool is_input_valid() const { return is_func_valid; };

  // graphix

  /// @brief Устанавливает флаг о том, что график мат. функции нарисован
  inline void graphix_show() { is_graphix_visible = true; }

  /// @brief Устанавливает флаг о том, что график мат. функции скрыт
  inline void graphix_hide() { is_graphix_visible = false; }

  inline bool is_graphix_hidden() const { return !is_graphix_visible; }

  // deriv

  /// @brief Устанавливает флаг, что график производной мат. функции нарисован
  inline void deriv_show() { is_deriv_visible = true; }

  /// @brief Устанавливает флаг о том, что график производной мат. функции скрыт
  inline void deriv_hide() { is_deriv_visible = false; }

  inline bool is_deriv_hidden() const { return !is_deriv_visible; }

  // setters

  /// @brief Устанавливает индекс всем кнопкам и полям
  void set_index(unsigned long long);

  /**
   * @brief Устанавливает текст в поле вывода ошибок
   * @param message: текст
   */
  inline void set_message(const std::string& message) { out_box->put(message); }

  /**
   * @brief Устанавливает текст в поле вывода для производной мат. функции
   * @param deriv_str: текст
   */
  inline void set_deriv_message(const std::string& deriv_str) {
    out_der_box->put(deriv_str);
  }

  // getters

  /**
   * @brief Возвращает значение введенной мат. функцию
   * @return std::string
   */
  inline std::string get_string() const { return in_box->get_string(); }

  /**
   * @brief Возвращает значение индекс текущего Function_box'а
   * @return unsigned long long
   */
  inline unsigned long long get_index() const {
    // (так как мы не храним этот индекс в качестве поля, берём от элемента)
    return draw_graphix_button->get_number();
  }

  // ~methods

 private:
  // vars

  // widgets

  /// @brief Кнопка для рисования графика мат. функции
  Numbed_button* draw_graphix_button;
  /// @brief Кнопка для скрытия графика мат. функции
  Numbed_button* hide_graphix_button;

  /// @brief Кнопка для рисования графика производной мат. функции
  Numbed_button* draw_deriv_button;
  /// @brief Кнопка для скрытия графика производной мат. функции
  Numbed_button* hide_deriv_button;
  /// @brief Поле для вывода текущей производной мат. функции
  Graph_lib::Out_box* out_der_box;

  /// @brief Поле для ввода мат. функции
  Graph_lib::In_box* in_box;
  /// @brief Поле для вывода ошибок по поводу введенной мат. функции
  Graph_lib::Out_box* out_box;

  /// @brief Кнопка для удаления текущего Function_box'а
  Numbed_button* rem_func_button;

  // flags

  /// @brief Флаг, сообщающий о валидности введенной мат. функции
  bool is_func_valid{false};

  /// @brief Флаг, сообщающий о видимости графика введенной мат. функции
  bool is_graphix_visible{false};

  /// @brief Флаг, сообщающий о видимости графика производной мат. функции
  bool is_deriv_visible{false};

  // ~vars
};

}  // namespace Graphix_calc