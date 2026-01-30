cmake_minimum_required(VERSION 3.12)
project(weapon_ball)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
  weapon_ball "src/weapon_ball/ball.cpp" "src/weapon_ball/line.cpp"
              "src/weapon_ball/object.cpp" "src/main.cpp")
target_link_libraries(weapon_ball raylib)
