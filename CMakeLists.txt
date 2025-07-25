set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
cmake_minimum_required(VERSION 3.14)
project(physics_engine)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG master
)
FetchContent_MakeAvailable(yaml-cpp)
add_executable(app
cli.cpp
mod/laws.cpp
mod/object.cpp
)
find_package(fmt REQUIRED)
target_link_libraries(app PRIVATE fmt::fmt)
target_include_directories(app PRIVATE mod)
target_link_libraries(app PRIVATE yaml-cpp)
