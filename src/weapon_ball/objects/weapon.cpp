#include "weapon_ball/objects/weapon.hpp"

Weapon::Weapon(std::shared_ptr<Ball> bearer, const std::string & sprite_path, float attack_power,
  float attack_speed)
: bearer(bearer),
  attack_power(attack_power),
  attack_speed(attack_speed),
  padding(0.f),
  angle(0.f),
  clockwise_rotation(true),
  draw_hitbox(false)
{
  set_sprite(sprite_path);
}

Weapon::~Weapon()
{
  UnloadTexture(sprite);
  UnloadImage(sprite_image);
}

void Weapon::update(float dt) { angle += PI * attack_speed * dt * (-1 + 2 * clockwise_rotation); }

void Weapon::draw()
{
  if (!bearer) return;

  Vector2 orbit_pos = bearer->pos;
  orbit_pos.y -= bearer->radius + sprite.height / 2.f + padding;

  Vector2 orbit_pos_anchor = {orbit_pos.x - sprite.width / 2.f, orbit_pos.y - sprite.height / 2.f};

  DrawTextureEx(sprite, Vector2Rotate(orbit_pos_anchor - bearer->pos, angle) + bearer->pos,
    angle * RAD2DEG, 1.0, WHITE);

  if (draw_hitbox) {
  }
}

bool is_colliding(Weapon & other);
void respond_collision(Weapon & other);

bool is_colliding(Ball & other);
void respond_collision(Ball & other);

const Texture2D & Weapon::get_sprite() { return sprite; }

// `width` and `height` parameters are optional, set -1 to not resize.
void Weapon::resize_sprite(int width, int height)
{
  int new_width = width < 0 ? sprite.width : width;
  int new_height = height < 0 ? sprite.height : height;

  ImageResize(&sprite_image, new_width, new_height);
  sprite = LoadTextureFromImage(sprite_image);
}

void Weapon::set_sprite(const std::string & sprite_path)
{
  sprite_image = LoadImage(sprite_path.c_str());
  sprite = LoadTextureFromImage(sprite_image);
}
