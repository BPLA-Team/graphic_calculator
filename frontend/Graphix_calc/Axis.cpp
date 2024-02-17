#include "Axis.h"

// std libs
using std::string;

// Graph_lib
using Graph_lib::Color;
using Graph_lib::Point;
using Graph_lib::Text;

// utility
#include "../utility/constants.h"
#include "../utility/utilities.h"
using namespace Frontend_consts;
using namespace Frontend_utilities;

namespace Graphix_calc {

Axis::Axis(Orientation orient, Point origin, pix_amount length,
           double _unit_intr, const std::string& label_text)
    // в этом случае за mark_intr берём unit_intr
    : unit_intr{_unit_intr},
      mark_intr{pix_amount(_unit_intr)},
      // надпись располагаем с отступом
      // IDK: насколько тут плох тернарный оператор?
      // (просто возникает проблема с запретом копирования Shape)
      label{orient == Orientation::vertical
                ? Point{origin.x - margin, origin.y - length / 2 + margin}
                : Point{origin.x + length / 2 - margin, origin.y - margin},
            label_text} {
  init(orient, origin, length);
}

Axis::Axis(Orientation orient, Graph_lib::Point origin, pix_amount length,
           double _unit_intr, pix_amount _mark_intr,
           const std::string& label_text)
    : unit_intr{_unit_intr},
      mark_intr{_mark_intr},
      // надпись располагаем с отступом
      // IDK: насколько тут плох тернарный оператор?
      // (просто возникает проблема с запретом копирования Shape)
      label{orient == Orientation::vertical
                ? Point{origin.x - margin, origin.y - length / 2 + margin}
                : Point{origin.x + length / 2 - margin, origin.y - margin},
            label_text} {
  init(orient, origin, length);
}

Axis::~Axis() {
  for (const auto& mark : marks)
    delete mark;
}

void Axis::draw_lines() const {
  Shape::draw_lines();
  label.draw();
  for (const auto& mark : marks)
    mark->draw();
  notches.draw();
}

void Axis::set_color(Color c) {
  Shape::set_color(c);
  label.set_color(c);
  notches.set_color(c);
}

void Axis::init(Orientation orient, Graph_lib::Point origin,
                pix_amount length) {
  switch (orient) {
    case Axis::horisontal: {
      // установка точек для линии оси
      Shape::add(Point{origin.x - length / 2, origin.y});
      Shape::add(Point{origin.x + length / 2, origin.y});

      // цикл по установке насечек и надписям к ним
      // (начинаем с единицы, так как начало координат очевидно)
      for (pix_amount i = 1; i < length / 2; i++) {
        // IDK: по идее, хорошо бы еще единичный отрезок рисовать, но тогда там длины разные
        // (из-за округления)

        // в этом случае насечка находится на нужном расстоянии от origin
        if (i % mark_intr == 0) {
          // добавляем насечки с двух сторон
          notches.add(Point{origin.x + i, origin.y + notch_side / 2},
                      Point{origin.x + i, origin.y - notch_side / 2});
          notches.add(Point{origin.x - i, origin.y + notch_side / 2},
                      Point{origin.x - i, origin.y - notch_side / 2});

          // также добавляем текст к этим насечкам

          // MEANS: надпись к насечке
          Text* mark = new Text(
              Point(origin.x + i - notch_side / 2, origin.y + margin),
              // (конвертируем, так как надписи к насечками в веществ.)
              format(
                  converted_to_real({origin.x + i, origin.y}, origin, unit_intr)
                      .x,
                  notch_marks_format_prec));
          mark->set_color(Graph_lib::Color::black);
          mark->set_font_size(notch_font_size);
          marks.push_back(mark);

          mark = new Text(
              Point(origin.x - i - notch_side, origin.y + margin),
              // (конвертируем, так как надписи к насечками в веществ.)
              format(
                  converted_to_real({origin.x - i, origin.y}, origin, unit_intr)
                      .x,
                  notch_marks_format_prec));
          mark->set_color(Graph_lib::Color::black);
          mark->set_font_size(notch_font_size);
          marks.push_back(mark);
        }
      }
      break;
    }
    case Axis::vertical: {
      // установка точек для линии оси
      Shape::add(Point{origin.x, origin.y + length / 2});
      Shape::add(Point{origin.x, origin.y - length / 2});

      // цикл по установке насечек и надписям к ним
      // (начинаем с единицы, так как начало координат очевидно)
      for (pix_amount i = 1; i < length / 2; i++) {
        // IDK: по идее, хорошо бы еще единичный отрезок рисовать, но тогда там длины разные
        // (из-за округления)

        // в этом случае насечка находится на нужном расстоянии от origin
        if (i % mark_intr == 0) {
          // добавляем насечки с двух сторон
          notches.add(Point{origin.x + notch_side / 2, origin.y + i},
                      Point{origin.x - notch_side / 2, origin.y + i});
          notches.add(Point{origin.x + notch_side / 2, origin.y - i},
                      Point{origin.x - notch_side / 2, origin.y - i});

          // также добавляем текст к этим насечкам

          // MEANS: надпись к насечке
          Text* mark = new Text(
              Point(origin.x + margin, origin.y + i + notch_side / 2),
              // (конвертируем, так как надписи к насечками в веществ.)
              format(
                  converted_to_real({origin.x, origin.y + i}, origin, unit_intr)
                      .y,
                  notch_marks_format_prec));
          mark->set_color(Graph_lib::Color::black);
          mark->set_font_size(notch_font_size);
          marks.push_back(mark);

          mark = new Text(
              Point(origin.x + margin, origin.y - i + notch_side / 2),
              // (конвертируем, так как надписи к насечками в веществ.)
              format(
                  converted_to_real({origin.x, origin.y - i}, origin, unit_intr)
                      .y,
                  notch_marks_format_prec));
          mark->set_color(Graph_lib::Color::black);
          mark->set_font_size(notch_font_size);
          marks.push_back(mark);
        }
      }
      break;
    }
  }
}

}  // namespace Graphix_calc