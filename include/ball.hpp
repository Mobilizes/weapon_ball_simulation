#ifndef BALL_HPP
#define BALL_HPP

#include "object.hpp"
#include "line.hpp"

#include <raymath.h>

class Ball : public Object
{
public:
  explicit Ball(Vector2 pos, float radius, Color color, Vector2 vel = Vector2Zero());

  void update(float dt) override;
  void draw() override;

  bool out_of_bounds();

  bool is_colliding(Line & other);
  void respond_collision(Line & other);

  bool is_colliding(Ball & other);
  void respond_collision(Ball & other);

  float mass = 100;

  Vector2 pos;
  Vector2 vel;
  float radius;

  Color color;
};

#endif  // BALL_HPP
