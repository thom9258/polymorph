cmake_minimum_required(VERSION 3.2)

project(examples VERSION 0.2.0)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -ggdb")
set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

message(STATUS "Fetching Libtester")
FetchContent_Declare(libtester
  GIT_REPOSITORY git@github.com:thom9258/libtester.git
  GIT_TAG main
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(libtester)

message(STATUS "Adding polymorph subdirectory")
add_subdirectory(../../ polymorph)

add_executable(${PROJECT_NAME} readme.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE polymorph::polymorph libtester)
