#pragma once

// std libs
#include <functional>
#include <string>

// Graph_lib
#include "../Graph_lib/Shapes.h"

// Graphix_calc
#include "Graphix.h"

// Backend
#include "../../backend.h"

namespace Graphix_calc {

/// @brief Фигура, представляющая собой график мат. функции, поделенный на
// сегменты, связанные с ОДЗ
class Segmented_graphix : public Graph_lib::Shape {
 public:
  Segmented_graphix() = default;

  /**
   * @brief Инициализирует новый экземпляр Segmented_graphix
   * @details Деление на сегменты происходит на прямоугольной области краями
   * которой и являются точки
   * @param _calc: лямбда-выражение от мат. функции
   * @param unit_intr: длина ед. отрезка
   * @param origin: начало координат
   * @param left_bottom: левая нижняя точка - начало области деления на сегменты
   * @param right_top: правая верхняя точка - конец области деления на сегменты
   */
  Segmented_graphix(std::function<double(double)> _calc, double unit_intr,
                    Graph_lib::Point origin, Graph_lib::Point left_bottom,
                    Graph_lib::Point right_top);

  Segmented_graphix(Graphix_calc::Graphix* graphix);

  ~Segmented_graphix();

  // methods

  void set_color(Graph_lib::Color c);

  inline Segmented_graphix& operator=(Graphix_calc::Graphix* graphix) {
    seged_graphix = std::vector<Graphix_calc::Graphix*>{graphix};
    return *this;
  }

  // ~methods

 private:
  // vars

  /// @brief Лямбда-выражение от мат. функции
  std::function<double(double)> calc;

  /// @brief Вещественные отрезки, где мат. функция определена
  std::vector<Math_calc::Segment> segs;

  /// @brief График мат. функции, поделенный на сегменты, связанные с ОДЗ
  std::vector<Graphix_calc::Graphix*> seged_graphix;

  // ~vars

  // methods

  void draw_lines() const override;

  /**
   * @param unit_intr: длина ед. отрезка,
   * @param origin: начало координат
   * @param left_bottom: левая нижняя точка - начало области деления на сегменты
   * @param right_top: правая верхняя точка - конец области деления на сегменты
   * @return std::vector<Math_calc::Segment>: вещественные отрезки, где мат.
   * функция определена
   */
  std::vector<Math_calc::Segment> segments(double unit_intr,
                                           Graph_lib::Point origin,
                                           Graph_lib::Point left_bottom,
                                           Graph_lib::Point right_top) const;

  /**
   * @return std::vector<Graphix_calc::Graphix*>: график мат. функции,
   * поделенный на сегменты, связанные с ОДЗ
   * @param unit_intr: длина ед. отрезка
   * @param origin: начало координат
   * @param left_bottom: левая нижняя точка - начало области деления на сегменты
   * @param right_top: правая верхняя точка - конец области деления на сегменты
   */
  std::vector<Graphix_calc::Graphix*> segmented_graphix(
      double unit_intr, Graph_lib::Point origin, Graph_lib::Point left_bottom,
      Graph_lib::Point right_top) const;

  // ~methods
};

}  // namespace Graphix_calc