cmake_minimum_required(VERSION 3.1)

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

project(polymorph VERSION 0.1.0)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -ggdb")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(polymorph_INCLUDES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/polymorph)

set(polymorph_INCLUDES
  ${polymorph_INCLUDES_DIR}/assign.hpp
  ${polymorph_INCLUDES_DIR}/detail.hpp
  ${polymorph_INCLUDES_DIR}/enumerate.hpp
  ${polymorph_INCLUDES_DIR}/filter.hpp
  ${polymorph_INCLUDES_DIR}/pipe.hpp
  ${polymorph_INCLUDES_DIR}/stream.hpp
  ${polymorph_INCLUDES_DIR}/tee.hpp
  ${polymorph_INCLUDES_DIR}/transform.hpp
)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE polymorph_INCLUDES)
