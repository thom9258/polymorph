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
  ${polymorph_INCLUDES_DIR}/types.hpp
  ${polymorph_INCLUDES_DIR}/piping.hpp
  ${polymorph_INCLUDES_DIR}/streaming.hpp
  ${polymorph_INCLUDES_DIR}/transforms.hpp
  ${polymorph_INCLUDES_DIR}/enumerate.hpp
  ${polymorph_INCLUDES_DIR}/filtering.hpp
)

add_library(${PROJECT_NAME} STATIC)

target_include_directories(${PROJECT_NAME} PUBLIC polymorph_INCLUDES)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
