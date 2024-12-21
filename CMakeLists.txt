cmake_minimum_required(VERSION 3.1)

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

project(polymorph VERSION 0.1.0)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -ggdb")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(polymorph_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/polymorph)

set(polymorph_INCLUDES
  ${polymorph_INCLUDE_DIRS}/assign.hpp
  ${polymorph_INCLUDE_DIRS}/detail.hpp
  ${polymorph_INCLUDE_DIRS}/enumerate.hpp
  ${polymorph_INCLUDE_DIRS}/filter.hpp
  ${polymorph_INCLUDE_DIRS}/pipe.hpp
  ${polymorph_INCLUDE_DIRS}/stream.hpp
  ${polymorph_INCLUDE_DIRS}/tee.hpp
  ${polymorph_INCLUDE_DIRS}/transform.hpp

  ${polymorph_INCLUDES_DIR}/polymorph.hpp
)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE polymorph_INCLUDE_DIRS)
