#include "Graphix_window.h"

// std libs
using std::string;
using std::vector;

// Graph_lib
using Graph_lib::Button;
using Graph_lib::Color;
using Graph_lib::Marks;
using Graph_lib::Point;

// Graphix_calc
using namespace Graphix_calc;

// utility
#include "../utility/constants.h"
using namespace Frontend_consts;
#include "../utility/utilities.h"
using namespace Frontend_utilities;

void Graphix_window::update_unit_intr(double new_unit_intr) {
  // если выбранный масштаб допустим
  if (new_unit_intr < max_unit_intr && new_unit_intr > min_unit_intr) {
    unit_intr = new_unit_intr;

    // отвязываем оси и высвобождаем память
    detach(*x_axis);
    detach(*y_axis);
    delete x_axis;
    delete y_axis;

    // создаём новые оси и задаём цвет

    x_axis = new Axis{Axis::Orientation::horizontal,
                      origin,
                      w() - func_box_w,
                      unit_intr,
                      mark_intr,
                      "X"};
    x_axis->set_color(Color::Color_type::dark_cyan);

    y_axis = new Axis{
        Axis::Orientation::vertical, origin, h(), unit_intr, mark_intr, "Y"};
    y_axis->set_color(Color::Color_type::dark_cyan);

    // привязываем новые оси
    attach(*x_axis);
    attach(*y_axis);

    // перерисовываем все графики
    for (size_t i = 0; i < enter_menu.size(); ++i)
      if (!enter_menu[i]->is_graphix_hidden()) update_graphix(i);

    // перерисовываем все производные
    for (size_t i = 0; i < enter_menu.size(); ++i)
      if (!enter_menu[i]->is_deriv_hidden()) update_deriv(i);

    // перерисовываем все точки, если они видны
    if (is_points_visible) update_points();
  }
}

void Graphix_window::update_inputed_func(size_t func_index,
                                         bool need_update_strings) {
  // если требуется, обновляем все строки
  // (не требоваться может при рекурсивном вызове)
  if (need_update_strings) {
    for (size_t i = 0; i < enter_menu.size(); i++)
      inputed_strings[i] = enter_menu[i]->get_string();
  }

  /// @brief Введенная строка - возможная строка мат. функции
  // (важно именно копировать её из соотв. вектора)
  string estimated_func_str = inputed_strings[func_index];

  /// @brief Вектор всех номеров мат. функций, которые зависят от возможной
  vector<size_t> dependencies;

  try {
    // раскрываем все зависимости вида y_n
    // (это модифицирующий входные данный в конструкторе класс)
    // (поэтому было важно копировать)
    // (так как в векторе введенных пользователем строк хочется)
    // (оставлять изначальные значения)
    Math_func::expose_func_str exposed{inputed_strings, estimated_func_str};

    // записываем зависимости
    // (к сожалению, лучше чем геттер - мы ничего не придумали)
    dependencies = exposed.get_dependencies();

    // обновляем все зависимые от возможной мат. функции
    for (const auto& n : dependencies) update_inputed_func(n - 1, false);

    // создаём мат. функцию по строке
    Math_func::function func{estimated_func_str};

    // если ранее не было выброшено исключений, то возможная мат. функция
    // валидна записываем её в соотв. вектор
    inputed_funcs[func_index] = func;

    // меняем состояние флага и устанавливаем пустую строку в поле вывода
    enter_menu[func_index]->input_valid();
    enter_menu[func_index]->set_message(empty_str);
  }

  catch (const std::exception& e) {
    // (пользователь мог указать номер еще не созданной мат. функции)
    if (func_index < enter_menu.size()) {
      // скрываем всё нарисованное в этом боксе до этого
      clear_graphix(func_index, false);
      clear_deriv(func_index, false);

      // меняем состояние флага и устанавливаем соотв. сообщение в поле вывода
      enter_menu[func_index]->input_invalid();
      enter_menu[func_index]->set_message(string{e.what()});

      // устанавливаем пустую строку в поле текущей производной мат. функции
      enter_menu[func_index]->set_deriv_message(empty_str);
    }
  }
}

void Graphix_window::fill_inputed_funcs() {
  // (так как соотв. функция принимает индекс, проходимся таким образом)
  for (size_t i = 0; i < enter_menu.size(); i++) update_inputed_func(i);
}

void Graphix_window::update_graphix(size_t func_index) {
  // записываем в вектор введенных мат. функций, что ввёл пользователь
  // (заодно проверяем)
  update_inputed_func(func_index);

  // если проверка успешна, рисуем график по введённой валидной мат. функции
  if (enter_menu[func_index]->is_input_valid()) {
    /// @brief Введенная мат. функция
    const Math_func::function& func = inputed_funcs[func_index];

    /// @brief График мат. функции, поделенный на отрезки
    Segmented_graphix* seged_graphix;

    // если есть переменная, используем конструктор сегментированного график
    if (func.has_var())
      seged_graphix = new Segmented_graphix(func.calculate, unit_intr, origin,
                                            {border_dist, h()}, {w(), 0});
    // иначе мы просто рисуем простой график
    else
      seged_graphix = new Segmented_graphix{new Graphix{
          func.calculate,
          converted_to_real({border_dist, h()}, origin, unit_intr).x,
          converted_to_real({w(), 0}, origin, unit_intr).x, origin, 2,
          unit_intr}};

    // чистим то, что лежало там до этого
    clear_graphix(func_index);

    // задаем цвет и привязываем к окну
    seged_graphix->set_color(Color::black);
    attach(*seged_graphix);

    // передаем во владение соотв. вектора
    graphics[func_index] = seged_graphix;
  }
}

void Graphix_window::clear_graphix(size_t func_index, bool need_delete) {
  /// @brief График мат. функции, поделенный на отрезки
  Graphix_calc::Segmented_graphix*& seged_graphix = graphics[func_index];

  // отвязываем от окна
  detach(*seged_graphix);

  // и чистим память (если необходимо)
  if (need_delete) delete seged_graphix;
}

void Graphix_window::update_deriv(size_t func_index) {
  // записываем в вектор введенных мат. функций, что ввёл пользователь
  //  (заодно проверяем)
  update_inputed_func(func_index);

  // если проверка прошла успешна, рисуем график производной по
  // введённой валидной мат. функции
  if (enter_menu[func_index]->is_input_valid()) {
    /// @brief Введенная мат. функция
    const Math_func::function& func = inputed_funcs[func_index];

    /// @brief График производной мат. функции, поделенный на отрезки
    Segmented_graphix* seged_deriv = new Segmented_graphix(
        func.differentiate, unit_intr, origin, {border_dist, h()}, {w(), 0});

    // чистим то, что лежало там до этого
    clear_deriv(func_index);

    // задаем цвет и привязываем к окну
    seged_deriv->set_color(Color::dark_red);
    attach(*seged_deriv);

    // передаем во владение соотв. вектора
    derivs[func_index] = seged_deriv;
  }
}

void Graphix_window::clear_deriv(size_t func_index, bool need_delete) {
  /// @brief График производной мат. функции, поделенный на отрезки
  Segmented_graphix*& seged_deriv = derivs[func_index];

  // отвязываем от окна
  detach(*seged_deriv);

  // и чистим память (если необходимо)
  if (need_delete) delete seged_deriv;
}

void Graphix_window::update_points() {
  // чистим память и окно от всех предыдущих точек
  clear_points();

  // так как у нас есть пересечения, нам надо заполнить каждую мат. функцию
  fill_inputed_funcs();

  // переводим границы экрана в вещественные, чтобы использовать для
  // бэкендовских функций
  Math_calc::Point left_bottom =
      converted_to_real({func_box_w, h()}, origin, unit_intr);
  Math_calc::Point right_top = converted_to_real({w(), 0}, origin, unit_intr);

  // FIXME: естественно, она не должна быть константой
  double point_prec = 0.0001;

  // проходимся по вектору, куда мат. функций и рисуем их экстремумы, корни
  // (проходиться нужно именно таким образом, ибо у нас вложенный перебор)
  for (size_t i = 0; i < enter_menu.size(); i++) {
    /// @brief Введенная мат. функция
    const Math_func::function& func = inputed_funcs[i];

    /// @brief Особые точки
    // (каждый раз перезаписывается)
    vector<Math_calc::Point> points;

    /// @brief Особые точки в виде символов
    Marks* marks = new Marks{empty_str};

    // отображаем корни и экстремумы, если мат. функция валидна
    if (enter_menu[i]->is_input_valid()) {
      // (вот именно для этой красивой передачи было перегружено явное
      // преобразование) записываем все корни в вектор особых точек
      points = vector<Math_calc::Point>(
          Math_calc::function_roots{func, left_bottom, right_top, point_prec});

      // записываем особые точки в марки, которые привязываем к окну
      // (выбираем соотв. символ)
      // TODO: создать пользовательский класс нужных для нас точек на экране

      marks = new Marks{"x"};
      for (const auto& root_point : points)
        marks->add(converted_to_pix(root_point, origin, unit_intr));
      attach(*marks);

      // добавляем в общий вектор всех особых точек на экране
      all_points.push_back(marks);

      // перезаписываем все экстремумы в вектор особых точек
      points = vector<Math_calc::Point>(Math_calc::function_extremes{
          func, left_bottom, right_top, point_prec});

      // перезаписываем особые точки в марки, которые привязываем к окну
      // (выбираем соотв. символ)
      Marks* marks = new Marks{"#"};
      for (const auto& extreme_point : points)
        marks->add(converted_to_pix(extreme_point, origin, unit_intr));
      attach(*marks);

      // добавляем в общий вектор всех особых точек на экране
      all_points.push_back(marks);
    }

    // проходимся по вектору, куда вводит мат. функций и рисуем их пересечения
    // (начинаем идти со следующего номера, чтобы не было самопересечения)
    for (size_t j = i + 1; j < enter_menu.size(); j++) {
      /// @brief Другая введенная мат. функция
      const Math_func::function& oth_func = inputed_funcs[j];

      // отображаем пересечения в том случае, если обе мат. функции валидны
      if (enter_menu[i]->is_input_valid() && enter_menu[j]->is_input_valid()) {
        // перезаписываем все пресечения в вектор особых точек
        points = vector<Math_calc::Point>(Math_calc::function_crosses{
            {func, oth_func}, left_bottom, right_top, point_prec});

        // перезаписываем особые точки в марки, которые привязываем к окну
        // (выбираем соотв. символ)
        marks = new Marks{"o"};
        for (const auto& cross_point : points)
          marks->add(converted_to_pix(cross_point, origin, unit_intr));
        attach(*marks);

        // добавляем в общий вектор всех особых точек на экране
        all_points.push_back(marks);
      }
    }
  }
}

// (так как точки мы чистим всегда, тут нету соотв. флага)
void Graphix_window::clear_points() {
  // проходимся по всем особым точкам, отображаемым в виде марков
  // (что удобно, если вектор всех точек пустой - лишнего удаления не случится)
  // (мы просто не зайдём в данный цикл)
  for (const auto& points : all_points) {
    // отвязываем от окна и чистим память
    detach(*points);
    delete points;
  }

  // изменяем размеры самого вектора
  all_points.clear();
}
