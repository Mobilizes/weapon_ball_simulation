#include "ball.hpp"

#include <raymath.h>

#include <stdexcept>

Ball::Ball(Vector2 pos, float radius, Color color, Vector2 vel) : Object()
{
  this->pos = pos;
  this->radius = radius;
  this->color = color;

  this->vel = vel;
  this->next_vel = vel;
}

void Ball::update(float dt)
{
  update_vel();
  pos += vel * dt;
}

void Ball::draw() { DrawCircleV(pos, radius, color); }

bool Ball::is_colliding(Line & other)
{
  float area = abs(Vector2CrossProduct(other.pos_start - this->pos, other.pos_end - this->pos)) / 2;
  float height = 2.0 * area / other.length();

  bool colliding = height <= radius;
  return colliding;
}

void Ball::respond_collision(Line & other)
{
  if (!is_colliding(other)) {
    throw std::runtime_error("Ball responding collision to non-colliding line!");
  }

  float t = Clamp(
    Vector2DotProduct(pos - other.pos_start, other.pos_end - other.pos_start) / other.length_sqr(),
    0.0, 1.0);

  Vector2 closest = other.pos_start * (1 - t) + other.pos_end * t;
  Vector2 normal = Vector2Normalize(pos - closest);

  Vector2 next_vel = vel - Vector2Scale(normal, 2.0 * Vector2DotProduct(vel, normal));
  set_next_vel(next_vel);
}

bool Ball::is_colliding(Ball & other)
{
  float total_radius = this->radius + other.radius;
  float distance_sqr = Vector2DistanceSqr(this->pos, other.pos);

  bool colliding = distance_sqr <= total_radius * total_radius;
  return colliding;
}

void Ball::respond_collision(Ball & other)
{
  if (!is_colliding(other)) {
    throw std::runtime_error("Ball responding collision to non-colliding ball!");
  }

  Vector2 next_vel =
    this->get_next_vel() -
    Vector2Scale(Vector2Scale(pos - other.pos, Vector2DotProduct(vel - other.vel, pos - other.pos) /
                                                   Vector2LengthSqr(pos - other.pos) +
                                                 EPSILON),
      (2 * other.mass) / (mass + other.mass + EPSILON));
  set_next_vel(next_vel);
}

Vector2 Ball::get_vel() { return vel; }
void Ball::update_vel() { vel = next_vel; }

Vector2 Ball::get_next_vel() { return next_vel; }
void Ball::set_next_vel(Vector2 next_vel) { this->next_vel = next_vel; }
