#pragma once

// std libs
#include <string>

// Graph_lib
#include "../Graph_lib/Shapes.h"

namespace Graphix_calc {

/// @brief Фигура, представляющая собой мат. ось координат
class Axis : public Graph_lib::Shape {
 public:
  enum Orientation { horizontal, vertical };

  /**
   * @brief Инициализирует новый экземпляр Axis
   * @param orient: ориентация
   * @param origin: центр коорд.
   * @param length: длина оси
   * @param _unit_intr: длина ед. отрезка
   * @param label_text: подпись
   */
  Axis(Orientation orient, Graph_lib::Point origin, pix_amount length,
       double _unit_intr, const std::string& label_text);

  /**
   * @brief Инициализирует новый экземпляр Axis
   * @param orient: ориентация
   * @param origin: центр коорд.
   * @param length: длина оси
   * @param _unit_intr: длина ед. отрезка
   * @param _mark_intr: длина марк. отрезка
   * @param label_text: подпись
   */
  Axis(Orientation orient, Graph_lib::Point origin, pix_amount length,
       double _unit_intr, pix_amount _mark_intr, const std::string& label_text);

  ~Axis();

  // methods

  /**
   * @brief Устанавливает все нужные точки
   * @param orient: ориентация
   * @param origin: начало координат
   * @param length: длина оси
   */
  void init(Orientation orient, Graph_lib::Point origin, pix_amount length);

  void draw_lines() const override;

  void set_color(Graph_lib::Color c);

  // ~methods

 private:
  // vars

  /// @brief Длина единичного отрезка
  double unit_intr;

  /// @brief Длина отмечаемого отрезка
  pix_amount mark_intr;

  /// @brief Надпись рядом с осью
  Graph_lib::Text label;

  /// @brief Насечки
  Graph_lib::Lines notches;

  /// @brief Надписи к насечкам
  std::vector<Graph_lib::Text*> marks;

  // ~vars
};

}  // namespace Graphix_calc