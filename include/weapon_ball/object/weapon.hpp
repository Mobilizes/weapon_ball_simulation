#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "weapon_ball/object/object.hpp"

#include "weapon_ball/object/ball.hpp"

#include <memory>
#include <string>

#define WEAPON_SPRITE_SIZE 64

class Weapon : Object
{
public:
  Weapon(std::shared_ptr<Ball> bearer, const std::string & sprite_path = "assets/placeholder.jpg",
    float attack_power = 0, float attack_speed = 0.5);
  ~Weapon();

  void update(float dt) override;
  void draw() override;

  void set_sprite(const std::string & sprite_path);

  float attack_power;
  float attack_speed;

  float padding = 5;

private:
  Texture2D sprite;

  std::shared_ptr<Ball> bearer;

  float angle;
  bool clockwise_rotation;
};

#endif  // WEAPON_HPP
