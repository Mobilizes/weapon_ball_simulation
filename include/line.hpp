#pragma once

#include "object.hpp"

class Line : public Object
{
public:
  explicit Line(Vector2 pos_start, Vector2 pos_end, float width, Color color);

  void update(float dt) override;
  void draw() override;

  float length();
  float length_sqr();

  Vector2 pos_start;
  Vector2 pos_end;
  float width;
  Color color;
};
