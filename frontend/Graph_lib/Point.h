#pragma once

using pix_amount = unsigned int;

namespace Graph_lib {

struct Point {
  inline Point() : x{0}, y{0} {}

  inline constexpr Point(pix_amount _x, pix_amount _y) : x{_x}, y{_y} {}

  // methods

  inline Point& operator+=(Point d) {
    x += d.x;
    y += d.y;
    return *this;
  }

  inline Point& operator-=(Point d) {
    x -= d.x;
    y -= d.y;
    return *this;
  }

  // ~methods

  // vars

  pix_amount x, y;

  // ~vars
};

inline Point operator+(Point a, Point b) { return a += b; }

inline Point operator-(Point a, Point b) { return a -= b; }

inline bool operator==(Point a, Point b) { return a.x == b.x && a.y == b.y; }

inline bool operator!=(Point a, Point b) { return !(a == b); }

}  // namespace Graph_lib
