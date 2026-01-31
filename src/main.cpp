#include "weapon_ball/object/ball.hpp"
#include "weapon_ball/object/line.hpp"
#include "weapon_ball/object/weapon.hpp"
#include "weapon_ball/utils/constants.hpp"

#include <raylib.h>
#include <raymath.h>

#include <memory>
#include <random>
#include <vector>

template <typename T>
class DynamicPartition
{
public:
  DynamicPartition() : partition(UNIFORM_PARTITION_ROW * UNIFORM_PARTITION_COL) {}

  std::vector<T> & get(int row, int col) { return partition[row * UNIFORM_PARTITION_COL + col]; }

private:
  std::vector<std::vector<T>> partition;
};

int main(void)
{
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Weapon Ball (Raylib)");
  SetTargetFPS(TARGET_FPS);

  std::random_device rd;
  std::mt19937 rng(rd());

  std::vector<std::shared_ptr<Ball>> balls = {
    std::make_shared<Ball>(Vector2{300, 300}, 30, RED, rng),
    std::make_shared<Ball>(Vector2{500, 300}, 30, BLUE, rng)};

  std::vector<std::shared_ptr<Line>> lines = {
    std::make_shared<Line>(Vector2{200, 100}, Vector2{200, 500}, 4, BLACK),
    std::make_shared<Line>(Vector2{600, 100}, Vector2{600, 500}, 4, BLACK),
    std::make_shared<Line>(Vector2{200, 100}, Vector2{600, 100}, 4, BLACK),
    std::make_shared<Line>(Vector2{200, 500}, Vector2{600, 500}, 4, BLACK),
  };

  std::vector<std::shared_ptr<Weapon>> weapons = {
    std::make_shared<Weapon>(balls[0], "assets/sword.png", 0, 0.5)};

  while (!WindowShouldClose()) {
    ClearBackground(RAYWHITE);
    DrawFPS(10, 10);

    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    float dt = GetFrameTime();

    DynamicPartition<std::shared_ptr<Ball>> ball_partition;
    DynamicPartition<std::shared_ptr<Line>> line_partition;

    for (std::shared_ptr<Ball> & ball : balls) {
      int start_row = std::max(0, (int)((ball->pos.y - ball->radius) / ROW_INC));
      int end_row =
        std::min(UNIFORM_PARTITION_ROW - 1, (int)((ball->pos.y + ball->radius) / ROW_INC));

      int start_col = std::max(0, (int)((ball->pos.x - ball->radius) / COL_INC));
      int end_col =
        std::min(UNIFORM_PARTITION_COL - 1, (int)((ball->pos.x + ball->radius) / COL_INC));

      for (int row = start_row; row <= end_row; ++row) {
        for (int col = start_col; col <= end_col; ++col) {
          ball_partition.get(row, col).push_back(ball);
        }
      }
    }

    for (std::shared_ptr<Line> line : lines) {
      int start_row = std::min(line->pos_start.y / ROW_INC, line->pos_end.y / ROW_INC);
      int end_row = std::max(line->pos_start.y / ROW_INC, line->pos_end.y / ROW_INC);

      int start_col = std::min(line->pos_start.x / COL_INC, line->pos_end.x / COL_INC);
      int end_col = std::max(line->pos_start.x / COL_INC, line->pos_end.x / COL_INC);

      for (int row = start_row; row <= end_row; ++row) {
        for (int col = start_col; col <= end_col; ++col) {
          line_partition.get(row, col).push_back(line);
        }
      }
    }

    for (int row = 0; row < UNIFORM_PARTITION_ROW; ++row) {
      for (int col = 0; col < UNIFORM_PARTITION_COL; ++col) {
        std::vector<std::shared_ptr<Ball>> & bp = ball_partition.get(row, col);
        std::vector<std::shared_ptr<Line>> & lp = line_partition.get(row, col);

        if (bp.size() + lp.size() < 2) continue;

        for (int i = 0; i < bp.size(); ++i) {
          std::shared_ptr<Ball> ball = bp[i];

          for (std::shared_ptr<Line> other : lp) {
            if (ball->is_colliding(*other)) {
              ball->respond_collision(*other);
            }
          }

          for (int j = i + 1; j < bp.size(); ++j) {
            std::shared_ptr<Ball> other = bp[j];

            if (ball->is_colliding(*other)) {
              ball->respond_collision(*other);
            }
          }
        }
      }
    }

    BeginDrawing();

    for (std::shared_ptr<Line> & line : lines) {
      line->update(dt);
      line->draw();
    }

    for (std::shared_ptr<Ball> & ball : balls) {
      ball->update(dt);
      ball->draw();
    }

    for (std::shared_ptr<Weapon> & weapon : weapons) {
      weapon->update(dt);
      weapon->draw();
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
