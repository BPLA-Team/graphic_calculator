#pragma once

// std libs
#include <string>
#include <utility>
#include <vector>

// Math_calc
#include "function_roots.h"
#include "math_base.h"

namespace Math_calc {

/// @brief Класс, хранящий в себе вектор точек - пересечений двух мат. функций
class function_crosses : public function_roots {
 public:
  /**
   * @brief Инициализирует новый экземпляр function_crosses
   * @details Поиск точек происходит на прямоугольной области, края которой -
   * точки
   * @param funcs: пара мат. функций
   * @param left_bottom: левая нижняя точка - начало области поиска точек
   * @param right_top: правая верхняя точка - конец области поиска точек
   * @param _precision: точность
   */
  function_crosses(std::pair<Math_func::function, Math_func::function> funcs,
                   Math_calc::Point left_bottom, Math_calc::Point right_top,
                   double _precision);

  // methods

  // (перегрузка явного преобразования типов)
  inline explicit operator std::vector<Math_calc::Point>() const {
    return points;
  }

  // ~methods

 private:
  // vars

  /// @brief Точность
  // (используем везде, поэтому сохраняем в качестве поля)
  double precision;

  /// @brief Одна из введенных мат. функций
  // (одна, так как нужно просто найти y, можно и в одну подставить)
  Math_func::function f;

  std::vector<Point> points;

  // ~vars

  // methods

  /**
   * @brief Считает все пересечения двух мат. функций
   * @param left_bottom: левая нижняя точка - начало области поиска точек
   * @param right_top: правая верхняя точка - конец области поиска точек
   * @return std::vector<Point>: точки пересечения двух мат. функций
   */
  std::vector<Point> crosses(Math_calc::Point left_bottom, Point right_top)
      const;  // (чтобы не хранить границы внутри класса - в аргументы)

  // ~methods
};

}  // namespace Math_calc