
#include "Segmented_graphix.h"

// std libs
#include <cmath>
using std::string;
using std::vector;

// Graph_lib
using Graph_lib::Point;

// Backend
using Math_calc::domain_segments;
using Math_calc::Segment;

// utility
#include "../utility/constants.h"
using namespace Frontend_consts;
#include "../utility/utilities.h"
using namespace Frontend_utilities;

namespace Graphix_calc {

Segmented_graphix::Segmented_graphix(std::function<double(double)> _calc,
                                     double unit_intr, Point origin,
                                     Graph_lib::Point left_bottom,
                                     Graph_lib::Point right_top)
    : calc{_calc},
      segs{segments(unit_intr, origin, left_bottom, right_top)},
      seged_graphix{
          segmented_graphix(unit_intr, origin, left_bottom, right_top)} {}

Segmented_graphix::Segmented_graphix(Graphix_calc::Graphix* graphix)
    : seged_graphix{std::vector<Graphix_calc::Graphix*>{graphix}} {}

Segmented_graphix::~Segmented_graphix() {
  for (const auto& graphix_part : seged_graphix) delete graphix_part;
}

void Segmented_graphix::draw_lines() const {
  Shape::draw_lines();
  for (const auto& graphix_part : seged_graphix) graphix_part->draw();
}

void Segmented_graphix::set_color(Graph_lib::Color c) {
  Shape::set_color(c);
  for (const auto& graphix_part : seged_graphix) graphix_part->set_color(c);
}

vector<Segment> Segmented_graphix::segments(double unit_intr,
                                            Graph_lib::Point origin,
                                            Graph_lib::Point left_bottom,
                                            Graph_lib::Point right_top) const {
  // экспериментально вычисленная удачная точность для деления на сегменты
  // (говно неработающее)
  // double prec_seg = ((double(r_border) / sqrt(unit_intr))) /
  // (abs(max_unit_intr - unit_intr));

  // FIXME: естественно, она не должна быть константой (надо исправить код выше)
  double prec_seg = 0.0001;

  // использование функции из бэкенда, которая дробит на веществ. числа
  vector<Segment> res = domain_segments(
      calc, converted_to_real(left_bottom, origin, unit_intr),
      converted_to_real(right_top, origin, unit_intr), prec_seg);
  return res;
}

vector<Graphix*> Segmented_graphix::segmented_graphix(
    double unit_intr, Graph_lib::Point origin, Graph_lib::Point left_bottom,
    Graph_lib::Point right_top) const {
  vector<Graphix*> res;
  // это количество точек идеально подходит под наши задачи
  // (по-хорошему тут геометрическая прогрессия, но ресурсов она требует)
  unsigned int point_amount = (4 / 3) * right_top.x * sqrt(unit_intr);
  for (const auto& seg : segs) {
    Graphix* f =
        new Graphix{calc, seg.start, seg.end, origin, point_amount, unit_intr};
    res.push_back(f);
  }
  return res;
}

}  // namespace Graphix_calc
