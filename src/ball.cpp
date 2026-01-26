#include "ball.hpp"

#include "constants.hpp"

#include <raymath.h>

#include <stdexcept>

Ball::Ball(Vector2 pos, float radius, Color color, Vector2 vel) : Object()
{
  this->pos = pos;
  this->radius = radius;
  this->color = color;
  this->vel = vel;
}

Ball::Ball(Vector2 pos, float radius, Color color, std::mt19937 & rng) : Object()
{
  this->pos = pos;
  this->radius = radius;
  this->color = color;
  this->vel = {std::uniform_real_distribution<float>(-100, 100)(rng),
    std::uniform_real_distribution<float>(-100, 100)(rng)};
}

void Ball::update(float dt)
{
  float max_vel_x = MAX_VEL_X == 0 ? MAXFLOAT : MAX_VEL_X;
  float max_vel_y = MAX_VEL_Y == 0 ? MAXFLOAT : MAX_VEL_Y;

  vel.x = Clamp(vel.x, -max_vel_x, max_vel_x);
  vel.y = Clamp(vel.y + GRAVITY * dt, -max_vel_y, max_vel_y);

  pos += vel * dt;
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

  float t = Clamp(Vector2DotProduct(pos - other.pos_start, other.pos_end - other.pos_start) /
                    (other.length_sqr() + EPSILON),
    0.0, 1.0);

  Vector2 closest = other.pos_start * (1 - t) + other.pos_end * t;
  Vector2 diff = pos - closest;
  Vector2 normal = Vector2Normalize(diff);

  float dot = Vector2DotProduct(vel, normal);

  if (dot < 0) {
    vel = vel - Vector2Scale(normal, 2.0 * dot);
  }

  pos = pos + Vector2Scale(normal, radius - Vector2Length(diff));
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

  Vector2 temp_vel = vel;

  vel = vel - Vector2Scale(
                Vector2Scale(pos - other.pos, Vector2DotProduct(vel - other.vel, pos - other.pos) /
                                                  Vector2LengthSqr(pos - other.pos) +
                                                EPSILON),
                (2 * other.mass) / (mass + other.mass + EPSILON));
  other.vel = other.vel - Vector2Scale(Vector2Scale(other.pos - pos,
                                         Vector2DotProduct(other.vel - temp_vel, other.pos - pos) /
                                             Vector2LengthSqr(other.pos - pos) +
                                           EPSILON),
                            (2 * mass) / (mass + other.mass + EPSILON));

  float mass_ratio = other.mass / (mass + other.mass + EPSILON);
  float penetration = radius + other.radius - Vector2Length(pos - other.pos);

  pos += Vector2Scale(Vector2Normalize(pos - other.pos), penetration * mass_ratio);
  other.pos -= Vector2Scale(Vector2Normalize(pos - other.pos), penetration * (1 - mass_ratio));
}
