#ifndef LINE_HPP
#define LINE_HPP

#include "weapon_ball/objects/object.hpp"

class Line : public Object
{
public:
  Line(Vector2 pos_start, Vector2 pos_end, float width, Color color);

  void update(float dt) override;
  void draw() override;

  float length();
  float length_sqr();

  Vector2 pos_start;
  Vector2 pos_end;
  float width;
  Color color;
};

#endif  // LINE_HPP
