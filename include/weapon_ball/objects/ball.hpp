#ifndef BALL_HPP
#define BALL_HPP

#include "weapon_ball/objects/object.hpp"
#include "weapon_ball/objects/line.hpp"

#include <raymath.h>

#include <random>

class Ball : public Object
{
public:
  Ball(Vector2 pos, float radius, Color color = GRAY, Vector2 vel = Vector2Zero());
  Ball(Vector2 pos, float radius, std::mt19937 & rng, Color color = GRAY);

  void update(float dt) override;
  void draw() override;

  bool out_of_bounds();

  bool is_colliding(Line & other);
  void respond_collision(Line & other);

  bool is_colliding(Ball & other);
  void respond_collision(Ball & other);

  void set_mass(float mass);
  float get_mass();

  float get_kinetic_energy();

  Vector2 vel;
  float radius;

  Color color;

private:
  float mass;
};

#endif  // BALL_HPP
