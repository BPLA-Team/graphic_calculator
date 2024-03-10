#include "Shapes.h"

// std libs
#include <algorithm>
#include <fstream>
#include <map>

namespace Graph_lib {

void Shape::draw() const {
  Fl_Color prev_color = fl_color();  // не существует хорошего портативного
                                     // способа получения текущего стиля
  fl_color(c.as_uint());
  fl_line_style(ls.style(), ls.w());
  draw_lines();
  fl_color(prev_color);  // reset color (к предыдущему) and style (к дефолтному)
  fl_line_style(0);
}

void Shape::draw_lines() const {
  // (точек должно быть больше одной)
  if (color().visibility() && 1 < points.size())
    for (unsigned int i = 1; i < points.size(); ++i)
      fl_line(int(points[i - 1].x), int(points[i - 1].y), int(points[i].x),
              int(points[i].y));
}

void Shape::move(int dx, int dy) {
  for (unsigned int i = 0; i < points.size(); ++i) {
    points[i].x += dx;
    points[i].y += dy;
  }
}

Shape::~Shape() {}

//-------------------------------------------------------------------------------------------------------------------------------

// RETURNS: расстояние до точки пересечения
// (если две линии (point_1,point_2) и (point_3,point_4) пересекаются)
inline std::pair<double, double> line_intersect(Point point_1, Point point_2,
                                                Point point_3, Point point_4,
                                                bool& parallel)

{
  double x1 = point_1.x;
  double x2 = point_2.x;
  double x3 = point_3.x;
  double x4 = point_4.x;
  double y1 = point_1.y;
  double y2 = point_2.y;
  double y3 = point_3.y;
  double y4 = point_4.y;

  double denom = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
  if (denom == 0) {
    parallel = true;
    return std::make_pair(0., 0.);
  }
  parallel = false;
  return std::make_pair(
      ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / denom,
      ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / denom);
}

//-------------------------------------------------------------------------------------------------------------------------------

void Open_polyline::draw_lines() const {
  if (fill_color().visibility()) {
    fl_color(fill_color().as_uint());
    fl_begin_complex_polygon();
    for (size_t i = 0; i < number_of_points(); ++i)
      fl_vertex(point(i).x, point(i).y);

    fl_end_complex_polygon();
    fl_color(color().as_uint());  // reset color
  }

  if (color().visibility()) Shape::draw_lines();
}

//-------------------------------------------------------------------------------------------------------------------------------

void Closed_polyline::draw_lines() const {
  Open_polyline::draw_lines();

  if (color().visibility())
    fl_line(point(number_of_points() - 1).x, point(number_of_points() - 1).y,
            point(0).x, point(0).y);
}

//-------------------------------------------------------------------------------------------------------------------------------

void Lines::draw_lines() const {
  if (color().visibility())
    for (size_t i = 1; i < number_of_points(); i += 2)
      fl_line(point(i - 1).x, point(i - 1).y, point(i).x, point(i).y);
}

//-------------------------------------------------------------------------------------------------------------------------------

void Text::draw_lines() const {
  int prev_font = fl_font();
  int prev_size = fl_size();
  fl_font(fnt.as_uint(), fnt_sz);
  fl_draw(lab.c_str(), point(0).x, point(0).y);
  fl_font(prev_font, prev_size);
}

//-------------------------------------------------------------------------------------------------------------------------------

// DOES: рисует 1 марку
// ARGS: расположение, символ
// (чисто вспомогательная)
void draw_mark(Point _loc, char c) {
  static const int dx = 4;
  static const int dy = 4;
  std::string m{c};
  fl_draw(m.c_str(), int(_loc.x - dx), int(_loc.y + dy));
}

void Marked_polyline::draw_lines() const {
  Open_polyline::draw_lines();
  for (size_t i = 0; i < number_of_points(); ++i)
    draw_mark(point(i), mark[i % mark.size()]);
}

//-------------------------------------------------------------------------------------------------------------------------------

std::map<std::string, Suffix::Encoding> suffix_map;

int init_suffix_map() {
  suffix_map["png"] = Suffix::png;
  suffix_map["PNG"] = Suffix::png;
  suffix_map["jpg"] = Suffix::jpg;
  suffix_map["JPG"] = Suffix::jpg;
  suffix_map["jpeg"] = Suffix::jpg;
  suffix_map["JPEG"] = Suffix::jpg;
  suffix_map["gif"] = Suffix::gif;
  suffix_map["GIF"] = Suffix::gif;
  suffix_map["bmp"] = Suffix::bmp;
  suffix_map["BMP"] = Suffix::bmp;
  return 0;
}

Suffix::Encoding get_encoding(const std::string& s)
// IDK: мне надо эти комментарии переводить?..
// try to deduce type from file name using a lookup table
{
  [[maybe_unused]] static int x = init_suffix_map();

  std::string::const_iterator p = std::find(s.begin(), s.end(), '.');
  if (p == s.end()) return Suffix::none;  // no suffix

  std::string suf{p + 1, s.end()};
  return suffix_map[suf];
}

bool can_open(const std::string& s)
// check if a file named s exists and can be opened for reading
{
  return static_cast<bool>(std::ifstream{s});
}

//-------------------------------------------------------------------------------------------------------------------------------

// somewhat overelaborate constructor
// because errors related to image files can be such a pain to debug
Image::Image(Point _loc, const std::string& s, Suffix::Encoding e)
    : width{0}, height{0}, text{_loc, ""} {
  add(_loc);

  if (!can_open(s)) {
    text.set_label("cannot open \"" + s + '\"');
    img_ptr = new Bad_image{30, 20};  // the "error image"
    return;
  }

  if (e == Suffix::none) e = get_encoding(s);

  switch (e) {
    case Suffix::png:
      img_ptr = new Fl_PNG_Image{s.c_str()};
      break;
    case Suffix::jpg:
      img_ptr = new Fl_JPEG_Image{s.c_str()};
      break;
    case Suffix::gif:
      img_ptr = new Fl_GIF_Image{s.c_str()};
      break;
    default:  // Unsupported image encoding
      text.set_label("unsupported file type \"" + s + '\"');
      img_ptr = new Bad_image{30, 20};  // the "error image"
  }
}

void Image::draw_lines() const {
  if (text.label() != "") text.draw_lines();

  if (width && height)
    img_ptr->Fl_Image::draw(point(0).x, point(0).y, width, height, cx, cy);
  else
    img_ptr->Fl_Image::draw(point(0).x, point(0).y);
}

void Image::move(int dx, int dy) {
  Shape::move(dx, dy);
  img_ptr->Fl_Image::draw(point(0).x, point(0).y);
}

}  // namespace Graph_lib
