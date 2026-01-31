cmake_minimum_required(VERSION 3.12)
project(weapon_ball)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
  weapon_ball
  "src/${PROJECT_NAME}/ball.cpp" "src/${PROJECT_NAME}/line.cpp"
  "src/${PROJECT_NAME}/object.cpp" "src/${PROJECT_NAME}/weapon.cpp"
  "src/main.cpp")

add_custom_command(
  TARGET weapon_ball
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E rm -rf "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
  COMMAND
    ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets")

target_include_directories(weapon_ball PUBLIC include)
target_link_libraries(weapon_ball raylib)
