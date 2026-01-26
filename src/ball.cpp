#include "ball.hpp"

#include "constants.hpp"

#include <raymath.h>

#include <stdexcept>

Ball::Ball(Vector2 pos, float radius, Color color, Vector2 vel) : Object()
{
  this->pos = pos;
  this->radius = radius;
  this->color = color;

  this->next_pos = pos;

  this->vel = vel;
  this->next_vel = vel;
}

void Ball::update(float dt)
{
  float max_vel_x = MAX_VEL_X == 0 ? MAXFLOAT : MAX_VEL_X;
  float max_vel_y = MAX_VEL_Y == 0 ? MAXFLOAT : MAX_VEL_Y;

  next_vel.x = Clamp(next_vel.x, -max_vel_x, max_vel_x);
  next_vel.y = Clamp(next_vel.y + GRAVITY * dt, -max_vel_y, max_vel_y);
  update_vel();

  next_pos += vel * dt;
  update_pos();
}

void Ball::draw()
{
  if (out_of_bounds()) return;

  DrawCircleV(pos, radius, color);
}

bool Ball::out_of_bounds()
{
  return pos.x < -radius || pos.x > WINDOW_WIDTH + radius || pos.y < -radius ||
         pos.y > WINDOW_HEIGHT + radius;
}

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
  Vector2 diff = pos - closest;
  Vector2 normal = Vector2Normalize(diff);

  next_vel = vel - Vector2Scale(normal, 2.0 * Vector2DotProduct(vel, normal));
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

  next_vel = vel - Vector2Scale(Vector2Scale(pos - other.pos,
                                  Vector2DotProduct(vel - other.vel, pos - other.pos) /
                                      Vector2LengthSqr(pos - other.pos) +
                                    EPSILON),
                     (2 * other.mass) / (mass + other.mass + EPSILON));
}

Vector2 Ball::get_pos() { return pos; }
void Ball::update_pos() { pos = next_pos; }

Vector2 Ball::get_next_pos() { return next_pos; }
void Ball::set_next_pos(Vector2 next_pos) { this->next_pos = next_pos; }

Vector2 Ball::get_vel() { return vel; }
void Ball::update_vel() { vel = next_vel; }

Vector2 Ball::get_next_vel() { return next_vel; }
void Ball::set_next_vel(Vector2 next_vel) { this->next_vel = next_vel; }
