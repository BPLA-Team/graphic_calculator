#pragma once

// Graph_lib
#include "../Graph_lib/Widgets.h"
#include "../Graph_lib/Window.h"

namespace Graphix_calc {

class Point_box : public Graph_lib::Widget {
 public:
  // упрощенный конструктор
  // (так как находится в углу окна, надо передавать размеры)
  Point_box(pix_amount window_w, pix_amount window_h,
            void cb_show(void*, void*), void cb_hide(void*, void*));

  ~Point_box();

  // methods

  void attach(Graph_lib::Window&);

  void detach(Graph_lib::Window&);

  // ~methods

 private:
  // vars

  Graph_lib::Button* show_button;
  Graph_lib::Button* hide_button;

  // ~vars
};

}  // namespace Graphix_calc