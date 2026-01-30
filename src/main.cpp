#include "weapon_ball/ball.hpp"
#include "weapon_ball/constants.hpp"
#include "weapon_ball/line.hpp"

#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <random>
#include <vector>

int main(void)
{
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "raylib [core] example - basic window");
  SetTargetFPS(TARGET_FPS);

  std::random_device rd;
  std::mt19937 rng(rd());

  std::vector<Ball> balls = {
    Ball({300, 300}, 30, RED, rng), Ball({500, 300}, 30, BLUE, rng)};

  std::vector<Line> lines = {
    Line({200, 100}, {200, 500}, 4, {0, 0, 0, 255}),
    Line({600, 100}, {600, 500}, 4, {0, 0, 0, 255}),
    Line({200, 100}, {600, 100}, 4, {0, 0, 0, 255}),
    Line({200, 500}, {600, 500}, 4, {0, 0, 0, 255}),
  };

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
