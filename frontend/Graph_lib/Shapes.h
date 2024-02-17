#pragma once

// std libs
#include <cmath>
#include <functional>
#include <stdexcept>
#include <string>
#include <vector>

// Graph_lib
#include "Point.h"
#include "fltk.h"

namespace Graph_lib {

// (cтандарт C++ не определяет никаких математических констант)
const double pi{std::acos(-1.0)};

//-------------------------------------------------------------------------------------------------------------------------------

// MEANS: цвет, с учетом прозрачности
// (пока что только полная не/прозрачность)
struct Color {
  enum Color_type {
    red = FL_RED,
    blue = FL_BLUE,
    green = FL_GREEN,
    yellow = FL_YELLOW,
    white = FL_WHITE,
    black = FL_BLACK,
    magenta = FL_MAGENTA,
    cyan = FL_CYAN,
    dark_red = FL_DARK_RED,
    dark_green = FL_DARK_GREEN,
    dark_yellow = FL_DARK_YELLOW,
    dark_blue = FL_DARK_BLUE,
    dark_magenta = FL_DARK_MAGENTA,
    dark_cyan = FL_DARK_CYAN
  };

  enum Transparency { invisible = 0, visible = 255 };

  inline Color(Color_type _c) : c{Fl_Color(_c)}, v{visible} {}

  inline Color(Color_type _c, Transparency _v)
      : c{Fl_Color(_c)}, v{static_cast<unsigned char>(_v)} {}

  inline Color(unsigned int _c) : c{Fl_Color(_c)}, v{visible} {}

  inline Color(Transparency _v)
      : c{Fl_Color()}, v{static_cast<unsigned char>(_v)} {}

  inline ~Color() = default;

  // methods

  inline unsigned int as_uint() const { return c; }

  inline char visibility() const { return v; }

  inline void set_visibility(Transparency _v) { v = _v; }

  // ~methods

 private:
  // vars

  Fl_Color c;
  unsigned char v;  // (только 0 или 1 на данный момент)

  // ~vars
};

//-------------------------------------------------------------------------------------------------------------------------------

struct Line_style {
  enum Line_style_type {
    solid = FL_SOLID,            // -------
    dash = FL_DASH,              // - - - -
    dot = FL_DOT,                // .......
    dashdot = FL_DASHDOT,        // - . - .
    dashdotdot = FL_DASHDOTDOT,  // -..-..
  };

  inline Line_style(Line_style_type _s) : s{_s}, width{0} {}

  inline Line_style(Line_style_type _points, pix_amount _width)
      : s{_points}, width{_width} {}

  inline Line_style(unsigned int _s) : s{_s}, width{0} {}

  // methods

  inline pix_amount w() const { return width; }

  inline unsigned int style() const { return s; }

  // ~methods

 private:
  // vars

  unsigned int s;
  pix_amount width;

  // ~vars
};

//-------------------------------------------------------------------------------------------------------------------------------

class Font {
 public:
  enum Font_type {
    helvetica = FL_HELVETICA,
    helvetica_bold = FL_HELVETICA_BOLD,
    helvetica_italic = FL_HELVETICA_ITALIC,
    helvetica_bold_italic = FL_HELVETICA_BOLD_ITALIC,
    courier = FL_COURIER,
    courier_bold = FL_COURIER_BOLD,
    courier_italic = FL_COURIER_ITALIC,
    courier_bold_italic = FL_COURIER_BOLD_ITALIC,
    times = FL_TIMES,
    times_bold = FL_TIMES_BOLD,
    times_italic = FL_TIMES_ITALIC,
    times_bold_italic = FL_TIMES_BOLD_ITALIC,
    symbol = FL_SYMBOL,
    screen = FL_SCREEN,
    screen_bold = FL_SCREEN_BOLD,
    zapf_dingbats = FL_ZAPF_DINGBATS
  };

  inline Font(Font_type _f) : f{_f} {}

  inline Font(unsigned int _f) : f{_f} {}

  // methods

  inline unsigned int as_uint() const { return f; }

  // ~methods

 private:
  // vars

  unsigned int f;

  // ~vars
};

//-------------------------------------------------------------------------------------------------------------------------------

// MEANS: абстрактная фигура
// (имеет дело с цветом и стилем и сохраняет последовательность строк)
class Shape {
 public:
  inline Shape() = default;

  inline Shape(std::initializer_list<Point> _points) {
    for (Point point : _points)
      add(point);
  }

  inline Shape(const Shape&) = delete;  // (предотвращение копирования)

  // methods

  inline Shape& operator=(const Shape&) =
      delete;  // (предотвращение копирования)

  void draw() const;  // (имеет дело с цветом и draw_lines)

  // ~methods

 protected:
  // methods

  inline void add(Point p) { points.push_back(p); }

  inline void set_point(int i, Point p) { points[i] = p; }

  virtual void draw_lines() const;  // (просто рисует соответствующие линии)

  // ~methods

 public:
  // methods

  virtual void move(int dx, int dy);

  inline void set_color(Color _color) { c = _color; }

  inline Color color() const { return c; }

  inline void set_style(Line_style sty) { ls = sty; }

  inline Line_style get_style() const { return ls; }

  inline void set_fill_color(Color _color) { f_c = _color; }

  inline Color fill_color() const { return f_c; }

  inline Point point(int i) const { return points[i]; }

  inline size_t number_of_points() const { return points.size(); }

  // ~methods

  virtual ~Shape() = 0;

 private:
  // vars

  std::vector<Point> points;  // (не используется ни одним из наследников)
  Color c{static_cast<Color>(fl_color())};
  Line_style ls{0};
  Color f_c{Color::invisible};

  // ~vars
};

//-------------------------------------------------------------------------------------------------------------------------------

// MEANS: простая линяя, сост. из двух точек
class Line : public Shape {
 public:
  inline Line(Point point_1, Point point_2) {
    add(point_1);
    add(point_2);
  }
};

//-------------------------------------------------------------------------------------------------------------------------------

// MEANS: открытая последовательность линий
class Open_polyline : public Shape {
 public:
  using Shape::Shape;

  // methods

  inline void add(Point p) { Shape::add(p); }

  void draw_lines() const override;

  // ~methods
};

//-------------------------------------------------------------------------------------------------------------------------------

// MEANS: закпытая последовательность линий
struct Closed_polyline : Open_polyline {
 public:
  using Open_polyline::Open_polyline;

  // methods

  void draw_lines() const override;

  // ~methods
};

//-------------------------------------------------------------------------------------------------------------------------------

// MEANS: независимые линии
class Lines : public Shape {
 public:
  inline Lines() = default;

  inline Lines(std::initializer_list<Point> _points) : Shape{_points} {
    if (_points.size() % 2)
      throw std::invalid_argument("odd number of points for Lines");
  }

  // methods

  void draw_lines() const override;

  void add(Point point_1, Point point_2) {
    Shape::add(point_1);
    Shape::add(point_2);
  }

  // ~methods
};

//-------------------------------------------------------------------------------------------------------------------------------

class Text : public Shape {
 public:
  // (точка находится внизу слева от первой буквы)
  inline Text(Point _loc, const std::string& s) : lab{s} { add(_loc); }

  // methods

  void draw_lines() const override;

  inline void set_label(const std::string& s) { lab = s; }

  inline std::string label() const { return lab; }

  inline void set_font(Font f) { fnt = f; }

  inline Font font() const { return Font{fnt}; }

  inline void set_font_size(unsigned int s) { fnt_sz = s; }

  inline unsigned int font_size() const { return fnt_sz; }

  // ~methods

 private:
  // vars

  std::string lab;
  Font fnt{static_cast<unsigned int>(fl_font())};
  unsigned int fnt_sz{(14 < fl_size()) ? static_cast<unsigned int>(fl_size())
                                       : 14};  // минимум 14

  // ~vars
};

//-------------------------------------------------------------------------------------------------------------------------------

class Marked_polyline : public Open_polyline {
 public:
  inline Marked_polyline(const std::string& _mark) : mark{_mark} {}

  inline Marked_polyline(const std::string& _mark,
                         std::initializer_list<Point> _points)
      : Open_polyline{_points}, mark{_mark} {}

  inline Marked_polyline(std::initializer_list<Point> _points)
      : Open_polyline{_points} {}

  // methods

  void draw_lines() const override;

  // ~methods

 private:
  // vars

  std::string mark{"*"};

  // ~vars
};

//-------------------------------------------------------------------------------------------------------------------------------

class Marks : public Marked_polyline {
 public:
  inline Marks(const std::string& m) : Marked_polyline{m} {
    set_color(Color{Color::invisible});
  }
};

//-------------------------------------------------------------------------------------------------------------------------------

class Mark : public Marks {
 public:
  inline Mark(Point _loc, char c) : Marks{std::string(1, c)} { add(_loc); }
};

class Bad_image : public Fl_Image {
 public:
  inline Bad_image(int h, int w) : Fl_Image{h, w, 0} {}

  // methods

  inline void draw(int x, int y, int, int, int, int) override {
    draw_empty(x, y);
  }

  // ~methods
};

//-------------------------------------------------------------------------------------------------------------------------------

struct Suffix {
  enum Encoding { none, png, jpg, gif, bmp };
};

Suffix::Encoding get_encoding(const std::string& s);

//-------------------------------------------------------------------------------------------------------------------------------

class Image : public Shape {
 public:
  Image(Point _loc, const std::string& s, Suffix::Encoding e = Suffix::none);

  inline ~Image() { delete img_ptr; }

  // methods

  void draw_lines() const override;

  inline void set_mask(Point _loc, pix_amount _width, pix_amount _height) {
    width = _width;
    height = _height;
    cx = _loc.x;
    cy = _loc.y;
  }

  void move(int dx, int dy) override;

  // ~methods

 private:
  // vars

  pix_amount width, height;
  pix_amount cx,
      cy;  // define "masking box" within image relative to position (cx,cy)
  Fl_Image* img_ptr;
  Text text;

  // ~vars
};

}  // namespace Graph_lib
