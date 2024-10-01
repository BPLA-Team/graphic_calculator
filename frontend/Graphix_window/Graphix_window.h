#pragma once

// std libs
#include <string>
#include <vector>

// Graph_lib
#include "../Graph_lib/Shapes.h"
#include "../Graph_lib/Widgets.h"
#include "../Graph_lib/Window.h"

// Graphix_calc
#include "../Graphix_calc/Axis.h"
#include "../Graphix_calc/Bothput_box.h"
#include "../Graphix_calc/Function_box.h"
#include "../Graphix_calc/Graphix.h"
#include "../Graphix_calc/Point_box.h"
#include "../Graphix_calc/Segmented_graphix.h"

// Backend
#include "../../backend.h"

/// @brief Окно, с полями для ввода мат. функций, возможностью построения их
/// графиков на сист. коорд.
class Graphix_window : public Graph_lib::Window {
 public:
  Graphix_window();

  /**
   * @brief Инициализирует новый экземпляр Graphix_window
   * @param left_corner: точка - левый верхний угол
   * @param _width: ширина
   * @param _height: высота
   * @param title: заголовок
   * @param _unit_intr: длина ед. отрезка
   */
  Graphix_window(Graph_lib::Point left_corner, pix_amount _width,
                 pix_amount _height, const std::string& title,
                 pix_amount _unit_intr);

  // methods

  /// @brief Запускает цикл ожидания нажатия кнопки и перерисовывает всё
  void wait_for_button();

  bool window_is_open() const { return !quit_button_pushed; }

 private:
  // vars

  // other

  /// @brief Длина единичного отрезка
  double unit_intr;

  /// @brief Начало координат
  Graph_lib::Point origin;

  /// @brief Введенные пользователем строки
  std::vector<std::string> inputed_strings;
  /// @brief Введенные пользователем валидные мат. функции
  std::vector<Math_func::function> inputed_funcs;

  // shapes

  /// @brief Горизонтальная ось
  Graphix_calc::Axis* x_axis;
  /// @brief Вертикальная ось
  Graphix_calc::Axis* y_axis;

  /// @brief Нарисованные пользователем графики мат. функций
  std::vector<Graphix_calc::Segmented_graphix*> graphics;
  /// @brief Нарисованные пользователем графики производных мат. функций
  std::vector<Graphix_calc::Segmented_graphix*> derivs;

  /// @brief Все особые точки графиков
  std::vector<Graph_lib::Marks*> all_points;

  /// @brief Линия - ограничитель системы координат от меню ввода
  Graph_lib::Line border;

  // widgets

  /// @brief Кнопка увеличения масштаба
  Graph_lib::Button incr_button;
  /// @brief Кнопка уменьшения масштаба
  Graph_lib::Button decr_button;
  /// @brief Кнопка, изменяющая масштаб по введенному пользователем
  Graph_lib::Button scale_button;
  /// @brief Поле для ввода пользовательского масштаба и вывода текущего
  Graphix_calc::Bothput_box scale_box;

  /// @brief Две кнопки, связанные с отображением особых точек графиков
  Graphix_calc::Point_box point_box;

  /// @brief Создания нового поля для ввода мат. функции
  Graph_lib::Button new_func_button;

  /// @brief Поля для ввода мат. функций и кнопки по управлению их графиков
  std::vector<Graphix_calc::Function_box*> enter_menu;

  /// @brief Кнопка выхода из программы
  Graph_lib::Button quit_button;

  // flags

  bool is_points_visible{false};

  bool some_button_pushed{false};
  bool quit_button_pushed{false};

  // ~vars

  // methods

  /// @brief Инициализирует всё то, что не было проиниц. в конструкторах
  void init() override;

  /// @brief Привязывает к окну все проиниц. виджеты и фигуры
  void initial_attach();

  // callbacks

  static void cb_incr_unit_intr(void*, void* widget);    // incr_button
  static void cb_decr_unit_intr(void*, void* widget);    // decr_button
  static void cb_change_unit_intr(void*, void* widget);  // scale_button

  static void cb_graphix_draw(
      void*, void* widget);  // enter_menu[i]->draw_graphix_button
  static void cb_graphix_hide(
      void*, void* widget);  // enter_menu[i]->hide_graphix_button

  static void cb_deriv_draw(void*,
                            void* widget);  // enter_menu[i]->draw_deriv_button
  static void cb_deriv_hide(void*,
                            void* widget);  // enter_menu[i]->draw_deriv_button

  static void cb_show_points(void*, void* widget);  // point_box.show_button
  static void cb_hide_points(void*, void* widget);  // point_box.hide_button

  static void cb_new_func(void*, void* widget);  // new_func_button
  static void cb_rem_func(void*,
                          void* widget);  // enter_menu[i]->rem_func_button

  static void cb_quit(void*, void* widget);  // quit_button

  // callback's voids

  /// @brief Увеличивает значение ед. отрезка
  void incr_unit_intr();  // cb_incr_unit_intr | update_unit_intr
  /// @brief Уменьшает значение ед. отрезка
  void decr_unit_intr();  // cb_decr_unit_intr | update_unit_intr
  /// @brief Устанавливает пользовательский масштаб (длину ед. отрезка по нему)
  void change_unit_intr();  // cb_change_unit_intr | update_unit_intr

  /**
   * @brief Рисует график мат. функции
   * @param func_index: индекс мат. функции
   */
  void draw_graphix(size_t func_index);  // cb_graphix_draw | update_graphix

  /**
   * @brief Скрывает график мат. функции (не удаляя его)
   * @param func_index: индекс мат. функции
   */
  void hide_graphix(size_t func_index);  // cb_graphix_hide | clear_graphix

  /**
   * @brief Рисует график производной мат. функции
   * @param func_index: индекс мат. функции
   */
  void draw_deriv(size_t func_index);  // cb_deriv_draw | update_deriv

  /**
   * @brief Скрывает график производной мат. функции (не удаляя его)
   * @param func_index: индекс мат. функции
   */
  void hide_deriv(size_t func_index);  // cb_deriv_hide | clear_deriv

  /// @brief Отображает все особые точки графиков мат. функций
  void show_points();  // cb_show_points | update_points
  /// @brief Скрывает все особые точки графиков мат. функций (удаляя их)
  void hide_points();  // cb_hide_points | clear_points

  /// @brief Добавляет новый бокс для ввода мат. функции
  void new_func_box();  // cb_new_func

  /**
   * @brief Удаляет бокс для ввода мат. функции
   * @param func_index: индекс мат. функции
   */
  void rem_func_box(size_t func_index);  // cb_rem_func

  /// @brief Завершает работу окна
  inline void quit()  // cb_quit
  {
    Fl_Window::hide();

    quit_button_pushed = true;
  }

  // updaters

  /**
   * @brief Обновляет значение единич. отрезка
   * @param new_unit_intr: новое значение единич. отрезка
   */
  void update_unit_intr(double new_unit_intr);

  /**
   * @brief Обновляет введенную мат. функцию
   * @param func_index: индекс мат. функции
   * @param need_update_strings: факт необходимости обновления введ. строк
   */
  void update_inputed_func(size_t func_index, bool need_update_strings = true);

  /// @brief Обновляет все введенные мат. функции
  void fill_inputed_funcs();

  /**
   * @brief Обновляет график мат. функции
   * @param func_index: индекс мат. функции
   */
  void update_graphix(size_t func_index);

  /**
   * @brief Удаляет график мат. функции
   * @param func_index: индекс мат. функции
   * @param need_delete: факт необходимости отчистки памяти
   */
  void clear_graphix(size_t func_index, bool need_delete = true);

  /**
   * @brief Обновляет график производной мат. функции
   * @param func_index: индекс мат. функции
   */
  void update_deriv(size_t func_index);

  /**
   * @brief Удаляет график производной мат. функции
   * @param func_index: индекс мат. функции
   * @param need_delete: факт необходимости отчистки памяти
   */
  void clear_deriv(size_t func_index, bool need_delete = true);

  /// @brief Обновляет особые точки графиков мат. функций
  void update_points();

  /// @brief Удаляет особые точки графиков мат. функций
  void clear_points();

  // ~methods
};