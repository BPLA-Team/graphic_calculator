#pragma once

// std libs
#include <string>
#include <vector>

// Math_calc
#include "function_roots.h"
#include "math_base.h"

namespace Math_calc {

/// @brief Класс, хранящий в себе вектор точек - лок. экстремумы мат. функции
class function_extremes : public function_roots {
 public:
  /**
   * @brief Инициализирует новый экземпляр function extremes
   * @details Поиск точек происходит на прямоугольной области, краями которой -
   * точки
   * @param _func: мат. функция
   * @param left_bottom: левая нижняя точка - начало области поиска точек
   * @param right_top: правая верхняя точка - конец области поиска точек
   * @param _precision: точность
   */
  function_extremes(Math_func::function _func, Math_calc::Point left_bottom,
                    Math_calc::Point right_top, double _precision);

  // methods

  // (перегрузка явного преобразования типов)
  inline explicit operator std::vector<Math_calc::Point>() const {
    return points;
  }

  // ~methods

 private:
  enum ExtremeType { pnt_min, pnt_max };

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
   * @return std::vector<Segment> подсегменты, где могут находиться экстремумы
   * @arg тип экстремума
   * @arg сегмент, на котором ищем
   */
  std::vector<Segment> estimated_segment(ExtremeType, Segment) const;

  /**
   * @return double: экстремум на интервале (значение x)
   * @details Используя метод золотого сечения
   * @arg тип экстремума
   * @arg сегмент, на котором ищем
   */
  double extreme_on_interval(ExtremeType, Segment) const;

  /**
   * @return std::vector<Point>: все локальные экстремумы (точки: пары вида
   * (x,y))
   * @param left_bottom: левая нижняя точка - начало области поиска точек
   * @param right_top: правая верхняя точка - конец области поиска точек
   */
  std::vector<Point> extremes(Math_calc::Point left_bottom,
                              Point right_top) const;

  // ~methods
};

}  // namespace Math_calc