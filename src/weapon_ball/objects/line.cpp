#include "weapon_ball/objects/line.hpp"

#include <raymath.h>

Line::Line(Vector2 pos_start, Vector2 pos_end, float width, Color color)
: Object(), pos_start(pos_start), pos_end(pos_end), width(width), color(color)
{
}

void Line::update(float dt) {}

void Line::draw() { DrawLineEx(pos_start, pos_end, width, color); }

float Line::length() { return Vector2Distance(pos_start, pos_end); }

float Line::length_sqr() { return Vector2DistanceSqr(pos_start, pos_end); }
