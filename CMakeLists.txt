cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME "graphic_calculator")
project(${PROJECT_NAME} CXX)

cmake_path(SET FRONTEND "${CMAKE_CURRENT_SOURCE_DIR}/frontend")
cmake_path(SET BACKEND "${CMAKE_CURRENT_SOURCE_DIR}/backend")

file(GLOB_RECURSE HEADERS
  "${FRONTEND}/*.h" "${FRONTEND}/*.hpp"
  "${BACKEND}/*.h" "${BACKEND}/*.hpp"
)

file(GLOB_RECURSE SOURCES
  "main.cpp"
  "${FRONTEND}/*.c" "${FRONTEND}/*.cpp"
  "${BACKEND}/*.c" "${BACKEND}/*.cpp"
)

set(FLTK_SKIP_FLUID True)
set(FLTK_SKIP_FORMS True)

find_package(FLTK 1.3.8 EXACT REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(SYSTEM ${FLTK_INCLUDE_DIR})
link_directories(${FLTK_INCLUDE_DIR}/../lib)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${FLTK_LIBRARIES} ${OPENGL_LIBRARIES})

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_link_libraries(${PROJECT_NAME} fltk_jpeg fltk_png fltk_z)
endif()

install(TARGETS ${PROJECT_NAME})
