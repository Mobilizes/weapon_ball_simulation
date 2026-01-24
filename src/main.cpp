#include "ball.hpp"
#include "line.hpp"
#include "constants.hpp"

#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <vector>

int main(void)
{
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "raylib [core] example - basic window");
  SetTargetFPS(TARGET_FPS);

  std::vector<Ball> balls = {Ball({300, 300}, 40, {255, 0, 0, 255}, {200, 50}),
    Ball({600, 300}, 40, {0, 0, 255, 255}, {-200, 0})};
  std::vector<Line> lines = {Line({100, 100}, {100, 500}, 4, {0, 0, 0, 255}),
    Line({700, 100}, {700, 500}, 4, {0, 0, 0, 255}),
    Line({100, 100}, {700, 100}, 4, {0, 0, 0, 255}),
    Line({100, 500}, {700, 500}, 4, {0, 0, 0, 255})};

  while (!WindowShouldClose()) {
    ClearBackground(RAYWHITE);
    DrawFPS(10, 10);

    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    float dt = GetFrameTime();

    std::vector<std::vector<std::vector<Ball *>>> ball_partition(
      UNIFORM_PARTITION_ROW, std::vector<std::vector<Ball *>>(UNIFORM_PARTITION_COL));
    std::vector<std::vector<std::vector<Line *>>> line_partition(
      UNIFORM_PARTITION_ROW, std::vector<std::vector<Line *>>(UNIFORM_PARTITION_COL));

    const int row_inc = ceil(WINDOW_HEIGHT / UNIFORM_PARTITION_ROW);
    const int col_inc = ceil(WINDOW_WIDTH / UNIFORM_PARTITION_COL);

    for (Ball & ball : balls) {
      for (float row_axis = 0, row = 0; row < UNIFORM_PARTITION_ROW; row_axis += row_inc, ++row) {
        if (!((ball.pos.y - ball.radius >= row_axis &&
                ball.pos.y - ball.radius <= row_axis + row_inc) ||
              (ball.pos.y + ball.radius >= row_axis &&
                ball.pos.y + ball.radius <= row_axis + row_inc))) {
          continue;
        }

        for (float col_axis = 0, col = 0; col < UNIFORM_PARTITION_COL; col_axis += col_inc, ++col) {
          if (!((ball.pos.x - ball.radius >= col_axis &&
                  ball.pos.x - ball.radius <= col_axis + col_inc) ||
                (ball.pos.x + ball.radius >= col_axis &&
                  ball.pos.x + ball.radius <= col_axis + col_inc))) {
            continue;
          }

          ball_partition[row][col].push_back(&ball);
        }
      }
    }

    for (Line & line : lines) {
      for (float row_axis = 0, row = 0; row < UNIFORM_PARTITION_ROW; row_axis += row_inc, ++row) {
        if ((line.pos_start.y < row_axis && line.pos_end.y < row_axis) ||
            (line.pos_start.y > row_axis + row_inc && line.pos_end.y > row_axis + row_inc)) {
          continue;
        }

        for (float col_axis = 0, col = 0; col < UNIFORM_PARTITION_COL; col_axis += col_inc, ++col) {
          if ((line.pos_start.x < col_axis && line.pos_end.x < col_axis) ||
              (line.pos_start.x > col_axis + col_inc && line.pos_end.x > col_axis + col_inc)) {
            continue;
          }

          line_partition[row][col].push_back(&line);
        }
      }
    }

    // for (Ball & ball : balls) {
    //   for (Line & other : lines) {
    //     if (ball.is_colliding(other)) {
    //       ball.respond_collision(other);
    //     }
    //   }
    //
    //   for (Ball & other : balls) {
    //     if (&ball == &other) continue;
    //     if (ball.is_colliding(other)) {
    //       ball.respond_collision(other);
    //     }
    //   }
    // }

    for (int row = 0; row < UNIFORM_PARTITION_ROW; ++row) {
      for (int col = 0; col < UNIFORM_PARTITION_COL; ++col) {
        if (ball_partition[row][col].size() + line_partition[row][col].size() < 2) continue;

        for (Ball * ball : ball_partition[row][col]) {
          for (Line other : lines) {
            if (ball->is_colliding(other)) {
              ball->respond_collision(other);
            }
          }

          for (Ball * other : ball_partition[row][col]) {
            if (ball == other) continue;
            if (ball->is_colliding(*other)) {
              ball->respond_collision(*other);
            }
          }
        }
      }
    }

    for (int row = 0; row < UNIFORM_PARTITION_ROW; ++row) {
      for (int col = 0; col < UNIFORM_PARTITION_COL; ++col) {
        std::cout << ball_partition[row][col].size() << "+" << line_partition[row][col].size()
                  << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;

    BeginDrawing();

    for (float row_axis = 0, row = 0; row < UNIFORM_PARTITION_ROW; row_axis += row_inc, ++row) {
      DrawLine(0, row_axis + row_inc, WINDOW_WIDTH, row_axis + row_inc, {0, 0, 0, 255});
    }

    for (float col_axis = 0, col = 0; col < UNIFORM_PARTITION_COL; col_axis += col_inc, ++col) {
      DrawLine(col_axis + col_inc, 0, col_axis + col_inc, WINDOW_HEIGHT, {0, 0, 0, 255});
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
