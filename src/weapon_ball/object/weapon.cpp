#include "weapon_ball/object/weapon.hpp"

Weapon::Weapon(std::shared_ptr<Ball> bearer, const std::string & sprite_path, float attack_power,
  float attack_speed)
: bearer(bearer), attack_power(attack_power), attack_speed(attack_speed)
{
  set_sprite(sprite_path);
}

Weapon::~Weapon() { UnloadTexture(sprite); }

void Weapon::update(float dt) { angle += PI * attack_speed * dt * (-1 + 2 * clockwise_rotation); }

void Weapon::draw()
{
  Vector2 orbit_pos = bearer->pos;
  orbit_pos.y -= bearer->radius + WEAPON_SPRITE_SIZE / 2.f + padding;

  Vector2 orbit_pos_anchor = {
    orbit_pos.x - WEAPON_SPRITE_SIZE / 2.f, orbit_pos.y - WEAPON_SPRITE_SIZE / 2.f};

  DrawTextureEx(sprite, Vector2Rotate(orbit_pos_anchor - bearer->pos, angle) + bearer->pos,
    angle * RAD2DEG, 1.0, WHITE);
}

void Weapon::set_sprite(const std::string & sprite_path)
{
  Image sprite_image = LoadImage(sprite_path.c_str());
  ImageResize(&sprite_image, WEAPON_SPRITE_SIZE, WEAPON_SPRITE_SIZE);

  sprite = LoadTextureFromImage(sprite_image);

  UnloadImage(sprite_image);
}
