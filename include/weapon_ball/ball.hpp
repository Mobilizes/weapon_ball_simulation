#ifndef BALL_HPP
#define BALL_HPP

#include "weapon_ball/object.hpp"
#include "weapon_ball/line.hpp"

#include <raymath.h>

#include <random>

class Ball : public Object
{
public:
  Ball(Vector2 pos, float radius, Color color, Vector2 vel = Vector2Zero());
  Ball(Vector2 pos, float radius, Color color, std::mt19937 & rng);

  void update(float dt) override;
  void draw() override;

  bool out_of_bounds();

  bool is_colliding(Line & other);
  void respond_collision(Line & other);

  bool is_colliding(Ball & other);
  void respond_collision(Ball & other);

  float get_kinetic_energy();

  float mass = 100;

  Vector2 pos;
  Vector2 vel;
  float radius;

  Color color;
};

#endif  // BALL_HPP
