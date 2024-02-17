#pragma once

// Graph_lib
#include "../Graph_lib/Widgets.h"

namespace Graphix_calc {

// MEANS: кнопка, которая имеет номер
class Numbed_button : public Graph_lib::Button {
 public:
  inline Numbed_button(Graph_lib::Point _loc, pix_amount _width,
                       pix_amount _height, const std::string& label,
                       void callback(void*, void*))
      : Graph_lib::Button{_loc, _width, _height, label, callback}, number{0} {}

  inline Numbed_button(Graph_lib::Point _loc, pix_amount _width,
                       pix_amount _height, const std::string& label,
                       unsigned long long _number, void callback(void*, void*))
      : Graph_lib::Button{_loc, _width, _height, label, callback},
        number{_number} {}

  ~Numbed_button() = default;

  // methods

  inline unsigned long long get_number() const { return number; }

  inline void set_number(unsigned long long value) { number = value; }

  // ~methods

 private:
  // vars

  unsigned long long number;

  // ~vars
};

}  // namespace Graphix_calc