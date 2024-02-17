
#include "Point_box.h"

// Graph_lib
using Graph_lib::Button;
using Graph_lib::Point;

// utility
#include "../utility/constants.h"

using namespace Frontend_consts;

namespace Graphix_calc {

Point_box::Point_box(pix_amount window_w, pix_amount window_h,
                     void cb_show(void*, void*), void cb_hide(void*, void*))
    : show_button{new Button{
          Point{window_w - btn_w * 2 - margin / 2, window_h - btn_h}, btn_w,
          btn_h, "Show", cb_show}},
      hide_button{new Button{Point{window_w - btn_w, window_h - btn_h}, btn_w,
                             btn_h, "Hide", cb_hide}} {}

Point_box::~Point_box() {
  delete show_button;
  delete hide_button;
}

void Point_box::attach(Graph_lib::Window& win) {
  win.attach(*show_button);
  win.attach(*hide_button);
  own = &win;
}

void Point_box::detach(Graph_lib::Window& win) {
  win.attach(*show_button);
  win.attach(*hide_button);
  own = &win;
}

}  // namespace Graphix_calc
