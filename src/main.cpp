#include "ball.hpp"
#include "line.hpp"
#include "constants.hpp"

#include <raylib.h>
#include <raymath.h>

#include <vector>

int main(void)
{
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "raylib [core] example - basic window");
  SetTargetFPS(TARGET_FPS);

  std::vector<Ball> balls = {Ball({300, 300}, 40, {255, 0, 0, 255}, {100, 50}),
    Ball({600, 300}, 40, {0, 0, 255, 255}, {-100, 0})};
  std::vector<Line> lines = {Line({100, 100}, {100, 500}, 4, {0, 0, 0, 255}),
    Line({700, 100}, {700, 500}, 4, {0, 0, 0, 255}),
    Line({100, 100}, {700, 100}, 4, {0, 0, 0, 255}),
    Line({100, 500}, {700, 500}, 4, {0, 0, 0, 255})};

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawFPS(10, 10);

    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    float dt = GetFrameTime();

    for (Line & line : lines) {
      line.draw();
    }

    for (Ball & ball : balls) {
      for (Line & other : lines) {
        if (ball.is_colliding(other)) {
          ball.respond_collision(other);
        }
      }

      for (Ball & other : balls) {
        if (&ball == &other) continue;
        if (ball.is_colliding(other)) {
          ball.respond_collision(other);
        }
      }
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
