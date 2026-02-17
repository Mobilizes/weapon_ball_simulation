#include "weapon_ball/objects/line.hpp"

#include <raymath.h>

// `vector_start` and `vector_end` are based on `pos`
Line::Line(Vector2 pos, Vector2 vector_start, Vector2 vector_end, float width, Color color)
: Object(pos), vector_start(vector_start), vector_end(vector_end), width(width), color(color)
{
}

void Line::update(float dt) {}

void Line::draw() { DrawLineEx(get_pos_start(), get_pos_end(), width, color); }

float Line::length() { return Vector2Distance(get_pos_start(), get_pos_end()); }
float Line::length_sqr() { return Vector2DistanceSqr(get_pos_start(), get_pos_end()); }

Vector2 Line::get_pos_start() { return pos + vector_start; }
Vector2 Line::get_pos_end() { return pos + vector_end; }
