#include "Graphix_window.h"

// std libs
#include <stdexcept>
using std::stod;
using std::string;
using std::to_string;
using std::vector;

// Graph_lib
using Graph_lib::Button;
using Graph_lib::Color;
using Graph_lib::Marks;
using Graph_lib::Point;

// Graphix_calc
using namespace Graphix_calc;

// utility
#include "../utility/constants.h"
#include "../utility/utilities.h"
using namespace Frontend_consts;
using namespace Frontend_utilities;

// temporary
#include "../../backend/temp_help.h"

void Graphix_window::wait_for_button() {
  while (!some_button_pushed && Fl::wait())
    ;

  // TEMP: временные выводы в консоль

  // cout << "some button pushed" << endl;
  // cout << "unit_intr: " << unit_intr << endl;
  // cout << "inputed_strings: ";
  // print(inputed_strings);
  // cout << "inputed_func_strs: ";
  // print(inputed_funcs);
  // cout << endl << endl;

  some_button_pushed = false;
  Fl::redraw();
}

// callbacks

void Graphix_window::cb_incr_unit_intr(void*, void* widget) {
  auto& btn = Graph_lib::reference_to<Button>(widget);
  dynamic_cast<Graphix_window&>(btn.window()).incr_unit_intr();
}

void Graphix_window::cb_decr_unit_intr(void*, void* widget) {
  auto& btn = Graph_lib::reference_to<Button>(widget);
  dynamic_cast<Graphix_window&>(btn.window()).decr_unit_intr();
}

void Graphix_window::cb_change_unit_intr(void*, void* widget) {
  auto& btn = Graph_lib::reference_to<Button>(widget);
  dynamic_cast<Graphix_window&>(btn.window()).change_unit_intr();
}

void Graphix_window::cb_graphix_draw(void*, void* widget) {
  auto& btn = Graph_lib::reference_to<Numbed_button>(widget);
  dynamic_cast<Graphix_window&>(btn.window()).draw_graphix(btn.get_number());
}

void Graphix_window::cb_graphix_hide(void*, void* widget) {
  auto& btn = Graph_lib::reference_to<Numbed_button>(widget);
  dynamic_cast<Graphix_window&>(btn.window()).hide_graphix(btn.get_number());
}

void Graphix_window::cb_deriv_draw(void*, void* widget) {
  auto& btn = Graph_lib::reference_to<Numbed_button>(widget);
  dynamic_cast<Graphix_window&>(btn.window()).draw_deriv(btn.get_number());
}

void Graphix_window::cb_deriv_hide(void*, void* widget) {
  auto& btn = Graph_lib::reference_to<Numbed_button>(widget);
  dynamic_cast<Graphix_window&>(btn.window()).hide_deriv(btn.get_number());
}

void Graphix_window::cb_show_points(void*, void* widget) {
  auto& btn = Graph_lib::reference_to<Button>(widget);
  dynamic_cast<Graphix_window&>(btn.window()).show_points();
}

void Graphix_window::cb_hide_points(void*, void* widget) {
  auto& btn = Graph_lib::reference_to<Button>(widget);
  dynamic_cast<Graphix_window&>(btn.window()).hide_points();
}

void Graphix_window::cb_new_func(void*, void* widget) {
  auto& btn = Graph_lib::reference_to<Button>(widget);
  dynamic_cast<Graphix_window&>(btn.window()).new_func_box();
}

void Graphix_window::cb_rem_func(void*, void* widget) {
  auto& btn = Graph_lib::reference_to<Numbed_button>(widget);
  dynamic_cast<Graphix_window&>(btn.window()).rem_func_box(btn.get_number());
}

void Graphix_window::cb_quit(void*, void* widget) {
  auto& btn = Graph_lib::reference_to<Button>(widget);
  dynamic_cast<Graphix_window&>(btn.window()).quit();
}

// callback's voids

void Graphix_window::incr_unit_intr() {
  update_unit_intr(unit_intr * unit_intr_coef);
  // (только при делении будет верное значение)
  scale_box.put_string(format(unit_intr / mark_intr, scale_format_prec));

  some_button_pushed = true;
}

void Graphix_window::decr_unit_intr() {
  update_unit_intr(unit_intr / unit_intr_coef);
  // (только при делении будет верное значение)
  scale_box.put_string(format(unit_intr / mark_intr, scale_format_prec));

  some_button_pushed = true;
}

void Graphix_window::change_unit_intr() {
  try {
    // домножаем пользовательский масштаб на длину маркированного отрезка
    double new_unit_intr = stod(scale_box.get_string()) * mark_intr;
    update_unit_intr(new_unit_intr);
  } catch (...)  // ошибка может вылететь от std::stod
  {
    // TODO: добавить уведомление, что были превышены макс./мин. масштаба
    scale_box.put_string("invalid input");
  }

  some_button_pushed = true;
}

void Graphix_window::draw_graphix(size_t func_index) {
  update_graphix(func_index);

  // обновляем флаг
  enter_menu[func_index]->graphix_show();

  some_button_pushed = true;
}

void Graphix_window::hide_graphix(size_t func_index) {
  // (мы просто прячем, нам не надо удалять его насовсем)
  clear_graphix(func_index, false);

  // обновляем флаг
  enter_menu[func_index]->graphix_hide();

  some_button_pushed = true;
}

void Graphix_window::draw_deriv(size_t func_index) {
  update_deriv(func_index);

  // обновляем флаг
  enter_menu[func_index]->deriv_show();

  // устанавливаем в соотв. поле строку мат. функции,
  // от которой рисуем график производной
  if (enter_menu[func_index]->is_input_valid())
    enter_menu[func_index]->set_deriv_message(
        "(" + inputed_funcs[func_index].get_func_str() + ")'");

  some_button_pushed = true;
}

void Graphix_window::hide_deriv(size_t func_index) {
  // (мы просто прячем, нам не надо удалять его насовсем)
  clear_deriv(func_index, false);

  // обновляем флаг
  enter_menu[func_index]->deriv_hide();

  // устанавливаем в соотв. поле пустую строку
  enter_menu[func_index]->set_deriv_message(empty_str);

  some_button_pushed = true;
}

void Graphix_window::show_points() {
  update_points();

  // обновляем флаг
  is_points_visible = true;

  some_button_pushed = true;
}

void Graphix_window::hide_points() {
  clear_points();

  // обновляем флаг
  is_points_visible = false;

  some_button_pushed = true;
}

void Graphix_window::new_func_box() {
  // если до увеличения вектор боксов был пуст, то мы обратно
  // двигаем кнопку создания нового поля для ввода мат. функции
  if (enter_menu.empty()) new_func_button.move(border_dist, 0);

  // создаем новый бокс (с индексом последний + 1 (= размер))
  Function_box* func_box =
      new Function_box{enter_menu.size(), cb_graphix_draw, cb_graphix_hide,
                       cb_rem_func,       cb_deriv_draw,   cb_deriv_hide};

  // привязываем его к окну
  attach(*func_box);

  // добавляем новый бокс в соотв. вектор
  enter_menu.push_back(func_box);

  // инициализируем (по умолчанию) следующий элемент в соотв. векторах

  graphics.push_back(new Segmented_graphix());
  derivs.push_back(new Segmented_graphix());

  inputed_strings.push_back(empty_str);
  inputed_funcs.push_back(empty_func);

  // если количество боксов стало максимально,
  // скрываем кнопку создания нового поля для ввода мат. функции
  if (enter_menu.size() == max_functions_amount) detach(new_func_button);

  some_button_pushed = true;
}

void Graphix_window::rem_func_box(size_t func_index) {
  // отвязываем соотв. бокс от окна
  enter_menu[func_index]->detach(*this);

  // проходимся по всем боксам начиная со следующего
  for (size_t j = func_index + 1; j < enter_menu.size(); ++j) {
    // двигаем их вверх и меняем номер на перед стоящий
    enter_menu[j]->move(0, -func_box_h);
    enter_menu[j]->set_index(enter_menu[j]->get_index() - 1);
  }

  // не забываем чистить память
  delete enter_menu[func_index];

  // также изменяем размеры соотв. векторов

  enter_menu.erase(enter_menu.begin() + func_index);

  inputed_strings.erase(inputed_strings.begin() + func_index);
  inputed_funcs.erase(inputed_funcs.begin() + func_index);

  // отвязываем график, график производной (там же чистим память)
  clear_graphix(func_index);
  clear_deriv(func_index);

  // изменяем размеры соотв. векторов

  graphics.erase(graphics.begin() + func_index);
  derivs.erase(derivs.begin() + func_index);

  // возвращаем кнопку создания нового поля для ввода мат. функции,
  // если количество боксов перестало быть максимальным
  if (enter_menu.size() == max_functions_amount - 1) attach(new_func_button);

  // если не осталось боксов, двигаем кнопку
  // создания нового поля для ввода мат. функции
  if (enter_menu.empty()) new_func_button.move(-border_dist, 0);

  some_button_pushed = true;
}
