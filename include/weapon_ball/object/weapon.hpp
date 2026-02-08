#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "weapon_ball/object/object.hpp"

#include "weapon_ball/object/ball.hpp"

#include <memory>
#include <string>

class Weapon : Object
{
public:
  Weapon(std::shared_ptr<Ball> bearer, const std::string & sprite_path = "assets/placeholder.jpg",
    float attack_power = 0, float attack_speed = 0.5);
  ~Weapon();

  void update(float dt) override;
  void draw() override;

  bool is_colliding(Weapon & other);
  void respond_collision(Weapon & other);

  bool is_colliding(Ball & other);
  void respond_collision(Ball & other);

  const Texture2D & get_sprite();
  void resize_sprite(int width = -1, int height = -1);
  void set_sprite(const std::string & sprite_path);

  float attack_power;
  float attack_speed;

  float padding;

  bool draw_hitbox;

private:
  std::shared_ptr<Ball> bearer;

  float angle;
  bool clockwise_rotation;

  Texture2D sprite;
  Image sprite_image;
};

#endif  // WEAPON_HPP
