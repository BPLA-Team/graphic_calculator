cmake_minimum_required(VERSION 3.20)

set(TARGET "graphic_calculator")

set(HEADERS

  # frontend
  # Graph_lib
  frontend/Graph_lib/Shapes.h
  frontend/Graph_lib/Widgets.h
  frontend/Graph_lib/Point.h
  frontend/Graph_lib/Window.h
  frontend/Graph_lib/fltk.h

  # Graphix_calc
  frontend/Graphix_calc/Axis.h
  frontend/Graphix_calc/Graphix.h
  frontend/Graphix_calc/Function_box.h
  frontend/Graphix_calc/Point_box.h
  frontend/Graphix_calc/Bothput_box.h
  frontend/Graphix_calc/Numbed_button.h
  frontend/Graphix_calc/Segmented_graphix.h

  # Graphix_window
  frontend/Graphix_window/Graphix_window.h

  # utility
  frontend/utility/utilities.h
  frontend/utility/constants.h

  # all in one
  frontend.h

  # backend
  # Math_calc
  backend/Math_calc/domain_segments.h
  backend/Math_calc/function_extremes.h
  backend/Math_calc/function_crosses.h
  backend/Math_calc/function_roots.h
  backend/Math_calc/math_base.h

  # Math_func
  backend/Math_func/expose_func_str.h
  backend/Math_func/function.h

  # utility
  backend/utility/utilities.h
  backend/utility/constants.h

  # temp
  backend/temp_help.h

  # all in one
  backend.h
)

set(SOURCES

  # frontend
  # Graph_lib
  frontend/Graph_lib/Shapes.cpp
  frontend/Graph_lib/Widgets.cpp
  frontend/Graph_lib/Window.cpp

  # Graphix_calc
  frontend/Graphix_calc/Axis.cpp
  frontend/Graphix_calc/Graphix.cpp
  frontend/Graphix_calc/Function_box.cpp
  frontend/Graphix_calc/Point_box.cpp
  frontend/Graphix_calc/Bothput_box.cpp
  frontend/Graphix_calc/Segmented_graphix.cpp

  # Graphix_window
  frontend/Graphix_window/Graphix_window_callbacks.cpp
  frontend/Graphix_window/Graphix_window_updaters.cpp
  frontend/Graphix_window/Graphix_window_init.cpp

  # utility
  frontend/utility/utilities.cpp

  # backend
  # Math_calc
  backend/Math_calc/domain_segments.cpp
  backend/Math_calc/function_extremes.cpp
  backend/Math_calc/function_crosses.cpp
  backend/Math_calc/function_roots.cpp

  # Math_func
  backend/Math_func/expose_func_str.cpp
  backend/Math_func/function.cpp
  backend/Math_func/function_validation.cpp

  # utility
  backend/utility/utilities.cpp

  # main
  main.cpp
)

project(${TARGET} CXX)

set(FLTK_SKIP_FLUID True)
set(FLTK_SKIP_FORMS True)

find_package(FLTK 1.3.8 EXACT REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(SYSTEM ${FLTK_INCLUDE_DIR})
link_directories(${FLTK_INCLUDE_DIR}/../lib)

add_executable(${TARGET} ${HEADERS} ${SOURCES})

target_link_libraries(${TARGET} ${FLTK_LIBRARIES} ${OPENGL_LIBRARIES})

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_link_libraries(${TARGET} fltk_jpeg fltk_png fltk_z)
endif()

install(TARGETS ${TARGET})
