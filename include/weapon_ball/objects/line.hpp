#ifndef LINE_HPP
#define LINE_HPP

#include "weapon_ball/objects/object.hpp"

class Line : public Object
{
public:
  Line(Vector2 pos, Vector2 vector_start = {-1, 0}, Vector2 vector_end = {1, 0}, float width = 4.f,
    Color color = BLACK);

  void update(float dt) override;
  void draw() override;

  float length();
  float length_sqr();

  Vector2 get_pos_start();
  Vector2 get_pos_end();

  float width;
  Color color;

private:
  Vector2 vector_start;
  Vector2 vector_end;
};

#endif  // LINE_HPP
