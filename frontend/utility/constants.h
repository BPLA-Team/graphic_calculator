#pragma once

// std libs
#include <string>

// Graphix_calc
#include "../Graphix_calc/Graphix.h"
#include "../Graphix_calc/Segmented_graphix.h"

// Backend
#include "../../backend.h"

namespace Frontend_consts {

const std::string empty_str = "";

// (мы можем использовать такую запись мат. функции не боясь за точки
// пересечения) (это связано с тем, что у нас в любом случае изначально
// enter_menu[i]->is_input_valid = false) (т.е. у только что созданных новых
// Function_box'ов не берется этот y = 0 в расчет для точек)

// MEANS: пустая (нулевая) мат. функция
const Math_func::function empty_func{"0"};

// MEANS: минимальное кол-во пикселей в ед. отрезке
constexpr pix_amount min_unit_intr = 2;
// MEANS: максимальное кол-во пикселей в ед. отрезке
constexpr pix_amount max_unit_intr = 32768;

// MEANS: максимальное количество вводимых мат. функций пользователем
constexpr unsigned long long int max_functions_amount = 7;

// MEANS: коэф. увеличения/уменьшения ед. отрезка при изменении масштаба
constexpr double unit_intr_coef = 2;

// MEANS: вспомогательный отступ
constexpr pix_amount margin = 20;

// MEANS: стандартная ширина кнопки
constexpr pix_amount btn_w = 70;
// MEANS: стандартная высота кнопки
constexpr pix_amount btn_h = 20;

// MEANS: сторона квадратной кнопки (кнопки изменения масштаба)
constexpr pix_amount scl_btn_side = 30;

// MEANS: кол-во пикселей, захваченных лейблом для in_box (т.е. "y = ")
constexpr pix_amount in_box_label_w = 30;

// MEANS: длина поля для ввода (исключая его лейбл "y = ")
constexpr pix_amount in_box_w = btn_w * 3 + margin - in_box_label_w;
// MEANS: высота поля для ввода
constexpr pix_amount in_box_h = 30;

// MEANS: длина поля вывода
constexpr pix_amount out_box_w = in_box_w + in_box_label_w;
// MEANS: высота поля вывода
constexpr pix_amount out_box_h = 20;

// MEANS: длина всего бокса, где пользователь может рисовать графики
constexpr pix_amount func_box_w = out_box_w;
// MEANS: высота всего бокса, где пользователь может рисовать графики
constexpr pix_amount func_box_h = in_box_h + 2 * btn_h + out_box_h + margin / 2;

// MEANS: расстояние, на котором находится линия-ограничитель
constexpr pix_amount border_dist = func_box_w + 1;

// MEANS: размер маркируемого отрезка, на котором ставится насечка
constexpr pix_amount mark_intr = 50;

// MEANS: стандартный размер текста для насечек
constexpr unsigned int notch_font_size = 12;

// MEANS: длина насечки
constexpr pix_amount notch_side = 8;

// MEANS: количество знаков после точки для подписей к насечкам на осях
constexpr unsigned int notch_marks_format_prec = 3;

// MEANS: количество знаков после точки для строки масштаба
constexpr unsigned int scale_format_prec = 5;

}  // namespace Frontend_consts
