## Структура проекта

```console
graphic_calculator/
|
| ─── frontend/
|       | ─── Graph_lib/
|       |       |---Shapes.h
|       |       |---Shapes.cpp
|       |       |---Widgets.h
|       |       |---Widgets.cpp
|       |       |---Window.h
|       |       |---Window.cpp
|       |       |---Point.h
|       |       `---fltk.h
|       |
|       | ─── Graphix_calc/
|       |       |---Axis.h
|       |       |---Axis.cpp
|       |       |---Graphix.h
|       |       |---Graphix.cpp
|       |       |---Segmented_graphix.h
|       |       |---Segmented_graphix.cpp
|       |       |
|       |       |---Function_box.h
|       |       |---Function_box.cpp
|       |       |---Point_box.h
|       |       |---Point_box.cpp
|       |       |---Bothput_box.h
|       |       |---Bothput_box.cpp
|       |       `---Numbed_button.h
|       |
|       | ─── Graphix_window/
|       |       |---Graphix_window.h
|       |       |---Graphix_window_init.cpp
|       |       |---Graphix_window_callbacks.cpp
|       |       `---Graphix_window_updaters.cpp
|       |
|       ` ─── utility/
|               |---constants.h
|               |---utilities.cpp
|               `---utility.h
|
| ─── backend/
|       | ─── Math_calc/ 
|       |       |---domain_segments.cpp
|       |       |---domain_segments.h
|       |       |
|       |       |---function_roots.h
|       |       |---function_roots.cpp
|       |       |---function_extremes.h
|       |       |---function_extremes.cpp
|       |       |---function_crosses.h
|       |       |---function_crosses.cpp
|       |       `---math_base.h
|       |
|       | ─── Math_func/ 
|       |       |---expose_func_str.h
|       |       |---expose_func_str.cpp
|       |       |
|       |       |---function.h
|       |       |---function.cpp
|       |       `---function_validation.cpp
|       |
|       | ─── utility/
|       |       |---constants.h
|       |       |---utilities.cpp
|       |       `---utility.h
|       |
|       `---temp_help.h
|
|
|---frontend.h
|---backend.h
`---main.cpp

```

## Некоторая идеология кода

Фронтенд: пиксели и графики
Бэкенд: числа с плавающей запятой и функции

std::string func_str 
        - строка обозначающая математическую функцию

Math_func::function func 
        - математическая функция (с методом calculate и differentiate)

Graphix_calc::Graphix graphix 
        - фигура, представляющая собой график, построенный по лямбде от мат. функции

Graphix_calc::Segmented_graphix seged_graphix 
        - фигура, представляющая собой тот же график, но правильный по О.Д.З.
