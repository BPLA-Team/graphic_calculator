#pragma once

// std libs
#include <string>
#include <vector>

// Math_calc
#include "math_base.h"

// Math_func
#include "../Math_func/function.h"

namespace Math_calc {

/// @brief Класс, хранящий в себе точки - пересеч. графика мат. функ. с осью Ox
class function_roots {
 public:
  function_roots() = default;

  /**
   * @brief Инициализирует новый экземпляр function_roots
   * @param _func: мат. функция
   * @param left_bottom: левая нижняя точка - начало области поиска точек
   * @param right_top: правая верхняя точка - конец области поиска точек
   * @param _precision: точность
   */
  function_roots(Math_func::function _func, Math_calc::Point left_bottom,
                 Math_calc::Point right_top, double _precision);

  // methods

  // (перегрузка явного преобразования типов)
  inline explicit operator std::vector<Math_calc::Point>() const {
    return points;
  }

  // ~methods

 protected:
  // methods

  /**
   * @return std::vector<Segment>: подсегменты, где могут находиться корни
   * @details Используя тот факт, что по разные стороны от точки-корня мат.
   * функция имеет разные знаки
   * @arg сегмент, на котором ищем
   */
  std::vector<Segment> estimated_segment(Segment) const;

  /**
   * @return double: корень на интервале (значение x)
   * @arg сегмент, на котором ищем
   */
  double root_on_interval(Segment) const;

  // ~methods

 private:
  // vars

  /// @brief Точность
  // (используем везде, поэтому сохраняем в качестве поля)
  double precision;

  /// @brief Введенная мат. функция
  Math_func::function f;

  std::vector<Point> points;

  // ~vars

  // methods

  /**
   * @return std::vector<Point>: все корни (точки: пары вида (x,y))
   * @param left_bottom: левая нижняя точка - начало области поиска точек
   * @param right_top: правая верхняя точка - конец области поиска точек
   */
  std::vector<Point> roots(Math_calc::Point left_bottom, Point right_top) const;

  // ~methods
};

}  // namespace Math_calc