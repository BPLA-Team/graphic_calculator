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

// MEANS: окно, с полями для ввода мат. функций, возможностью построения их графиков на сист. коорд.
class Graphix_window : public Graph_lib::Window {
 public:
  Graphix_window();

  // ARGS: точка - левый верхний угол, ширина, высота, заголовок, длина ед. отрезка
  Graphix_window(Graph_lib::Point left_corner, pix_amount _width,
                 pix_amount _height, const std::string& title,
                 pix_amount _unit_intr);

  // methods

  // DOES: запускает цикл ожидания нажатия кнопки и перересовывает всё в этом случае
  void wait_for_button();

  bool window_is_open() const { return !quit_button_pushed; }

 private:
  // vars

  // other

  // MEANS: длина единичного отрезка
  double unit_intr;

  // MEANS: начало координат
  Graph_lib::Point origin;

  // MEANS: введенные пользователем строки
  std::vector<std::string> inputed_strings;
  // MEANS: введенные пользователем валидные мат. функции
  std::vector<Math_func::function> inputed_funcs;

  // shapes

  // MEANS: горизонтальная ось
  Graphix_calc::Axis* x_axis;
  // MEANS: вертикальная ось
  Graphix_calc::Axis* y_axis;

  // MEANS: нарисованные пользователем графики мат. функций
  std::vector<Graphix_calc::Segmented_graphix*> graphics;
  // MEANS: нарисованные пользователем графики производных мат. функций
  std::vector<Graphix_calc::Segmented_graphix*> derivs;

  // MEANS: все особые точки графиков
  std::vector<Graph_lib::Marks*> all_points;

  // MEANS: линия - ограничитель системы координат от меню ввода
  Graph_lib::Line border;

  // widgets

  // MEANS: кнопка увеличения масштаба
  Graph_lib::Button incr_button;
  // MEANS: кнопка уменьшения масштаба
  Graph_lib::Button decr_button;
  // MEANS: кнопка, изменяющая масштаб по введенному пользователем
  Graph_lib::Button scale_button;
  // MEANS: поле для ввода пользовательского масштаба и вывода текущего
  Graphix_calc::Bothput_box scale_box;

  // MEANS: две кнопки, связанные с отображением особых точек графиков
  Graphix_calc::Point_box point_box;

  // MEANS: создания нового поля для ввода мат. функции
  Graph_lib::Button new_func_button;

  // MEANS: поля для ввода мат. функций и кнопки по управлению их графиков, производных
  std::vector<Graphix_calc::Function_box*> enter_menu;

  // MEANS: кнопка выхода из программы
  Graph_lib::Button quit_button;

  // flags

  bool is_points_visible{false};

  bool some_button_pushed{false};
  bool quit_button_pushed{false};

  // ~vars

  // methods

  // DOES: инициализирует всё то, что не было проиниц. в конструкторах
  void init() override;

  // DOES: привязывает к окну все проиниц. виджеты и фигуры
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

  // DOES: увеличивает значение ед. отрезка
  void incr_unit_intr();  // cb_incr_unit_intr | update_unit_intr
  // DOES: уменьшает значение ед. отрезка
  void decr_unit_intr();  // cb_decr_unit_intr | update_unit_intr
  // DOES: устанавливает пользовательский масштаб (длину ед. отрезка по нему)
  void change_unit_intr();  // cb_change_unit_intr | update_unit_intr

  // DOES: рисует график мат. функции
  // ARGS: индекс мат. функции
  void draw_graphix(size_t func_index);  // cb_graphix_draw | update_graphix
  // DOES: скрывает график мат. функции (не удаляя его)
  // ARGS: индекс мат. функции
  void hide_graphix(size_t func_index);  // cb_graphix_hide | clear_graphix

  // DOES: рисует график производной мат. функции
  // ARGS: индекс мат. функции
  void draw_deriv(size_t func_index);  // cb_deriv_draw | update_deriv
  // DOES: скрывает график производной мат. функции (не удаляя его)
  // ARGS: индекс мат. функции
  void hide_deriv(size_t func_index);  // cb_deriv_hide | clear_deriv

  // DOES: отображает все особые точки графиков мат. функций
  void show_points();  // cb_show_points | update_points
  // DOES: скрывает все особые точки графиков мат. функций (удаляя их)
  void hide_points();  // cb_hide_points | clear_points

  // DOES: добавляет новый бокс для ввода мат. функции
  void new_func_box();  // cb_new_func
  // DOES: удаляет бокс для ввода мат. функции
  // ARGS: индекс мат. функции
  void rem_func_box(size_t func_index);  // cb_rem_func

  // DOES: завершает работу окна
  inline void quit()  // cb_quit
  {
    Fl_Window::hide();

    quit_button_pushed = true;
  }

  // updaters

  // DOES: обновляет значение единич. отрезка
  // ARGS: новое значение единич. отрезка
  void update_unit_intr(double new_unit_intr);

  // DOES: обновляет введенную мат. функцию
  // ARGS: индекс мат. функции, факт необходимости обновления введ. строк
  void update_inputed_func(size_t func_index, bool need_update_strings = true);
  // DOES: обновляет все введенные мат. функции
  void fill_inputed_funcs();

  // DOES: обновляет график мат. функции
  // ARGS: индекс мат. функции
  void update_graphix(size_t func_index);
  // DOES: удаляет график мат. функции
  // ARGS: индекс мат. функции, факт необоходимости отчистки памяти
  void clear_graphix(size_t func_index, bool need_delete = true);

  // DOES: обновляет график производной мат. функции
  // ARGS: индекс мат. функции
  void update_deriv(size_t func_index);
  // DOES: удаляет график производной мат. функции
  // ARGS: индекс мат. функции, факт необоходимости отчистки памяти
  void clear_deriv(size_t func_index, bool need_delete = true);

  // DOES: обновляет особые точки графиков мат. функций
  void update_points();
  // DOES: удаляет особые точки графиков мат. функций
  void clear_points();

  // ~methods
};