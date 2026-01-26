#include "ball.hpp"
#include "line.hpp"
#include "constants.hpp"

#include <raylib.h>
#include <raymath.h>

#include <chrono>
#include <iostream>
#include <random>
#include <vector>

int main(void)
{
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "raylib [core] example - basic window");
  SetTargetFPS(TARGET_FPS);

  std::vector<Ball> balls = {Ball({300, 300}, 30, {255, 0, 0, 255}, {100, 50}),
    Ball({500, 300}, 30, {0, 0, 255, 255}, {-100, 0})};

  std::vector<Line> lines = {
    Line({200, 100}, {200, 500}, 4, {0, 0, 0, 255}),
    Line({600, 100}, {600, 500}, 4, {0, 0, 0, 255}),
    Line({200, 100}, {600, 100}, 4, {0, 0, 0, 255}),
    Line({200, 500}, {600, 500}, 4, {0, 0, 0, 255}),
    Line({400, 100}, {400, 500}, 4, {0, 0, 0, 255}),
  };

  // std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
  // for (int i = 0; i < 1000; ++i) {
  //   balls.push_back(Ball({std::uniform_real_distribution<float>(250, 550)(rng),
  //                          std::uniform_real_distribution<float>(150, 450)(rng)},
  //     3, {0, 255, 0, 255},
  //     {std::uniform_real_distribution<float>(-100, 100)(rng),
  //       std::uniform_real_distribution<float>(-100, 100)(rng)}));
  // }

  while (!WindowShouldClose()) {
    ClearBackground(RAYWHITE);
    DrawFPS(10, 10);

    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    float dt = GetFrameTime();

    std::vector<std::vector<std::vector<Ball *>>> ball_partition(
      UNIFORM_PARTITION_ROW, std::vector<std::vector<Ball *>>(UNIFORM_PARTITION_COL));
    std::vector<std::vector<std::vector<Line *>>> line_partition(
      UNIFORM_PARTITION_ROW, std::vector<std::vector<Line *>>(UNIFORM_PARTITION_COL));

    for (Ball & ball : balls) {
      int start_row = std::max(0, (int)((ball.pos.y - ball.radius) / ROW_INC));
      int end_row =
        std::min(UNIFORM_PARTITION_ROW - 1, (int)((ball.pos.y + ball.radius) / ROW_INC));

      int start_col = std::max(0, (int)((ball.pos.x - ball.radius) / COL_INC));
      int end_col =
        std::min(UNIFORM_PARTITION_COL - 1, (int)((ball.pos.x + ball.radius) / COL_INC));

      for (int row = start_row; row <= end_row; ++row) {
        for (int col = start_col; col <= end_col; ++col) {
          ball_partition[row][col].push_back(&ball);
        }
      }
    }

    for (Line & line : lines) {
      int start_row = std::min(line.pos_start.y / ROW_INC, line.pos_end.y / ROW_INC);
      int end_row = std::max(line.pos_start.y / ROW_INC, line.pos_end.y / ROW_INC);

      int start_col = std::min(line.pos_start.x / COL_INC, line.pos_end.x / COL_INC);
      int end_col = std::max(line.pos_start.x / COL_INC, line.pos_end.x / COL_INC);

      for (int row = start_row; row <= end_row; ++row) {
        for (int col = start_col; col <= end_col; ++col) {
          line_partition[row][col].push_back(&line);
        }
      }
    }

    for (int row = 0; row < UNIFORM_PARTITION_ROW; ++row) {
      for (int col = 0; col < UNIFORM_PARTITION_COL; ++col) {
        if (ball_partition[row][col].size() + line_partition[row][col].size() < 2) continue;

        for (int i = 0; i < ball_partition[row][col].size(); ++i) {
          Ball * ball = ball_partition[row][col][i];

          for (Line * other : line_partition[row][col]) {
            if (ball->is_colliding(*other)) {
              ball->respond_collision(*other);
            }
          }

          for (int j = i + 1; j < ball_partition[row][col].size(); ++j) {
            Ball * other = ball_partition[row][col][j];

            if (ball->is_colliding(*other)) {
              ball->respond_collision(*other);
            }
          }
        }
      }
    }

    BeginDrawing();

    for (float row_axis = 0, row = 0; row < UNIFORM_PARTITION_ROW; row_axis += ROW_INC, ++row) {
      DrawLine(0, row_axis + ROW_INC, WINDOW_WIDTH, row_axis + ROW_INC, {0, 0, 0, 255});
    }

    for (float col_axis = 0, col = 0; col < UNIFORM_PARTITION_COL; col_axis += COL_INC, ++col) {
      DrawLine(col_axis + COL_INC, 0, col_axis + COL_INC, WINDOW_HEIGHT, {0, 0, 0, 255});
    }

    for (Line & line : lines) {
      line.draw();
    }

    for (Ball & ball : balls) {
      ball.update(dt);
      ball.draw();
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
