#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "weapon_ball/object.hpp"

class Weapon : Object
{
public:
  Weapon();

  void update(float dt) override;
  void draw() override;

  int attack;

private:
  Texture2D sprite;
};

#endif  // WEAPON_HPP
