#include "Graphix_window.h"

// std libs
#include <stdexcept>
using std::string;
using std::vector;

// Graph_lib
using Graph_lib::Color;
using Graph_lib::Point;

// Graphix_calc
using namespace Graphix_calc;

// utility
#include "../utility/constants.h"
using namespace Frontend_consts;

// TODO: придумать, как подразбить на функции, не нарушая запрета копирования

Graphix_window::Graphix_window()
    : Graph_lib::Window({10, 10}, 1000, 750, "FIDocalcus"),
      unit_intr{50.0},
      // точка начала системы координат смещена вправо, чтобы графики и оси не
      // заезжали на меню
      origin{(w() + func_box_w) / 2, h() / 2},
      border{Point{border_dist, 0}, Point{border_dist, h()}},
      // кнопки изменения масштаба находятся справа и являются квадратами
      incr_button{Graph_lib::Point{w() - scl_btn_side, 0 + btn_h}, scl_btn_side,
                  scl_btn_side, "+", cb_incr_unit_intr},
      decr_button{
          Graph_lib::Point{w() - scl_btn_side, 0 + btn_h + scl_btn_side},
          scl_btn_side, scl_btn_side, "-", cb_decr_unit_intr},
      scale_button{
          Graph_lib::Point{in_box_w + in_box_label_w - btn_w, h() - in_box_h},
          btn_w, in_box_h, "Scale", cb_change_unit_intr},
      scale_box{Graph_lib::Point{in_box_label_w, h() - in_box_h},
                in_box_w - btn_w, in_box_h, "1:"},
      point_box{w(), h(), cb_show_points, cb_hide_points},
      new_func_button{Graph_lib::Point{border_dist, 0}, btn_w, btn_h, "New",
                      cb_new_func},
      quit_button{Graph_lib::Point{w() - btn_w, 0}, btn_w, btn_h, "Quit",
                  cb_quit}

{
  init();
}

Graphix_window::Graphix_window(Graph_lib::Point left_corner, pix_amount _width,
                               pix_amount _height, const string& title,
                               pix_amount _unit_intr)
    : Graph_lib::Window(left_corner, _width, _height, title),
      unit_intr{double(_unit_intr)},
      // точка начала системы координат смещена вправо, чтобы графики и оси не
      // заезжали на меню
      origin{(w() + func_box_w) / 2, h() / 2},
      border{Point{border_dist, 0}, Point{border_dist, h()}},
      // кнопки изменения масштаба находятся справа и являются квадратами
      incr_button{Graph_lib::Point{w() - scl_btn_side, 0 + btn_h}, scl_btn_side,
                  scl_btn_side, "+", cb_incr_unit_intr},
      decr_button{
          Graph_lib::Point{w() - scl_btn_side, 0 + btn_h + scl_btn_side},
          scl_btn_side, scl_btn_side, "-", cb_decr_unit_intr},
      scale_button{
          Graph_lib::Point{in_box_w + in_box_label_w - btn_w, h() - in_box_h},
          btn_w, in_box_h, "Scale", cb_change_unit_intr},
      scale_box{Graph_lib::Point{in_box_label_w, h() - in_box_h},
                in_box_w - btn_w, in_box_h, "1:"},
      point_box{w(), h(), cb_show_points, cb_hide_points},
      new_func_button{Graph_lib::Point{border_dist, 0}, btn_w, btn_h, "New",
                      cb_new_func},
      quit_button{Graph_lib::Point{w() - btn_w, 0}, btn_w, btn_h, "Quit",
                  cb_quit}

{
  init();
}

void Graphix_window::init() {
  // установка интервала изменения размеров окна
  // (а именно нулевого)
  size_range(w(), h(), w(), h());

  // задаём цвет окну
  // this->color(Color::white);

  // задаем цвет ограничивающей линии
  border.set_color(Color::black);

  // инициализируем первые элементы соотв. векторов
  // (так как с самого начала у нас есть 1 бокс для ввода)

  inputed_strings.push_back(empty_str);
  inputed_funcs.push_back(empty_func);

  Function_box* func_box =
      new Function_box{0,           cb_graphix_draw, cb_graphix_hide,
                       cb_rem_func, cb_deriv_draw,   cb_deriv_hide};
  enter_menu.push_back(func_box);

  graphics.push_back(new Segmented_graphix());
  derivs.push_back(new Segmented_graphix());

  // создаём оси с заданным в конструкторе значением ед. отрезка

  x_axis = new Axis{Axis::Orientation::horizontal,
                    origin,
                    w() - func_box_w,
                    unit_intr,
                    mark_intr,
                    "X"};
  y_axis = new Axis{
      Axis::Orientation::vertical, origin, h(), unit_intr, mark_intr, "Y"};

  // задаём цвет этим осям
  x_axis->set_color(Color::Color_type::dark_cyan);
  y_axis->set_color(Color::Color_type::dark_cyan);

  // привязываем всё созданное к окну
  initial_attach();
}

void Graphix_window::initial_attach() {
  attach(border);
  attach(*x_axis);
  attach(*y_axis);
  attach(quit_button);
  attach(incr_button);
  attach(decr_button);
  attach(new_func_button);
  attach(scale_button);
  attach(scale_box);

  attach(*enter_menu[0]);
  attach(point_box);
}
