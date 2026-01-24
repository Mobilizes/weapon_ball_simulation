#pragma once

#include "object.hpp"
#include "line.hpp"

#include <raymath.h>

class Ball : public Object
{
public:
  explicit Ball(Vector2 pos, float radius, Color color, Vector2 vel = Vector2Zero());

  void update(float dt) override;
  void draw() override;

  bool is_colliding(Line & other);
  void respond_collision(Line & other);

  bool is_colliding(Ball & other);
  void respond_collision(Ball & other);

  Vector2 get_vel();
  void update_vel();
  Vector2 get_next_vel();
  void set_next_vel(Vector2 next_vel);

  float mass = 100;

  Vector2 pos;
  float radius;

  Color color;

private:
  Vector2 next_vel;
  Vector2 vel;
};
