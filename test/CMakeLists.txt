cmake_minimum_required(VERSION 3.2)

project(test VERSION 0.1.0)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -ggdb")
set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# find_package (polymorph
# CONFIG REQUIRED
# PATHS "../build/install" NO_DEFAULT_PATH
# )
#
# add_executable(${PROJECT_NAME} test.cpp)
# target_link_libraries(${PROJECT_NAME} PRIVATE polymorph::polymorph)


# add_subdirectory(../ 3rdparty/polymorph)
# add_executable(${PROJECT_NAME} test.cpp)
# target_link_libraries(${PROJECT_NAME} PRIVATE polymorph::polymorph)

#-------------------------------------------------------------------------
# Fetch Polymorph
# ------------------------------------------------------------------------
include(FetchContent)
message(STATUS "Including Polymorph")
FetchContent_Declare(
polymorph
GIT_REPOSITORY git@github.com:thom9258/polymorph.git
GIT_TAG main
GIT_SHALLOW TRUE
GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(polymorph)

add_executable(${PROJECT_NAME} test.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE polymorph)
