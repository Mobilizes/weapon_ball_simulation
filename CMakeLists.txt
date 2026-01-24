CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
project(weapon_ball)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(weapon_ball
  "src/ball.cpp"
  "src/main.cpp"
  "src/line.cpp"
  "src/object.cpp"
)
target_include_directories(weapon_ball PUBLIC include)
target_link_libraries(weapon_ball raylib)
