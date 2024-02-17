#include "Function_box.h"

// Graphix_calc
using Graphix_calc::Numbed_button;

// Graph_lib
using Graph_lib::In_box;
using Graph_lib::Out_box;
using Graph_lib::Point;

// utility
#include "../utility/constants.h"
using namespace Frontend_consts;

namespace Graphix_calc {

Function_box::Function_box(unsigned long long int box_index,
                           void cb_graphix_draw(void*, void*),
                           void cb_graphix_hide(void*, void*),
                           void cb_rem_func(void*, void*),
                           void cb_deriv_draw(void*, void*),
                           void cb_deriv_hide(void*, void*))
    : draw_graphix_button{new Numbed_button{
          Point{0, func_box_h * pix_amount(box_index) + in_box_h}, btn_w, btn_h,
          "Draw", box_index, cb_graphix_draw}},
      hide_graphix_button{new Numbed_button{
          Point{btn_w + margin / 2,
                func_box_h * pix_amount(box_index) + in_box_h},
          btn_w, btn_h, "Hide", box_index, cb_graphix_hide}},
      draw_deriv_button{new Numbed_button{
          Point{btn_w + margin / 2,
                func_box_h * pix_amount(box_index) + in_box_h + btn_h},
          btn_w, btn_h, "Draw", box_index, cb_deriv_draw}},
      hide_deriv_button{new Numbed_button{
          Point{(btn_w + margin / 2) * 2,
                func_box_h * pix_amount(box_index) + in_box_h + btn_h},
          btn_w, btn_h, "Hide", box_index, cb_deriv_hide}},
      out_der_box{new Out_box{
          Point{0, func_box_h * pix_amount(box_index) + in_box_h + btn_h},
          btn_w, btn_h, empty_str}},
      // in_box_label_w: необходимо отступить расстояние, где находится "y = "
      in_box{
          new In_box{Point{in_box_label_w, func_box_h * pix_amount(box_index)},
                     in_box_w, in_box_h, "y = "}},
      out_box{new Out_box{
          Point{0, func_box_h * pix_amount(box_index) + in_box_h + 2 * btn_h},
          out_box_w, out_box_h, empty_str}},
      rem_func_button{new Numbed_button{
          Point{(btn_w + margin / 2) * 2,
                func_box_h * pix_amount(box_index) + in_box_h},
          btn_w, btn_h, "Remove", box_index, cb_rem_func}} {}

Function_box::~Function_box() {
  // так как в классе мы храним указатели, а память резервируем в конструкторе,
  // в деструкторе надобно всё освободить

  delete in_box;
  delete draw_graphix_button;
  delete hide_graphix_button;
  delete rem_func_button;
  delete out_der_box;
  delete draw_deriv_button;
  delete hide_deriv_button;
  delete out_box;
}

void Function_box::attach(Graph_lib::Window& win) {
  // try to decomment this :)
  // win.attach(*this);
  win.attach(*in_box);
  win.attach(*draw_graphix_button);
  win.attach(*hide_graphix_button);
  win.attach(*rem_func_button);
  win.attach(*out_der_box);
  win.attach(*draw_deriv_button);
  win.attach(*hide_deriv_button);
  win.attach(*out_box);
  own = &win;
}

void Function_box::detach(Graph_lib::Window& win) {
  // try to decomment this :)
  // win.detach(*this);
  win.detach(*in_box);
  win.detach(*draw_graphix_button);
  win.detach(*hide_graphix_button);
  win.detach(*rem_func_button);
  win.detach(*out_der_box);
  win.detach(*draw_deriv_button);
  win.detach(*hide_deriv_button);
  win.detach(*out_box);
  own = &win;
}

void Function_box::move(int dx, int dy) {
  in_box->move(dx, dy);
  draw_graphix_button->move(dx, dy);
  hide_graphix_button->move(dx, dy);
  rem_func_button->move(dx, dy);
  out_der_box->move(dx, dy);
  draw_deriv_button->move(dx, dy);
  hide_deriv_button->move(dx, dy);
  out_box->move(dx, dy);
}

void Function_box::set_index(unsigned long long value) {
  draw_graphix_button->set_number(value);
  hide_graphix_button->set_number(value);
  rem_func_button->set_number(value);
  draw_deriv_button->set_number(value);
  hide_deriv_button->set_number(value);
}

}  // namespace Graphix_calc