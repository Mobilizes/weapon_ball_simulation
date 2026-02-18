#include "weapon_ball/objects/object.hpp"

Object::Object(Vector2 pos) : id(count++), pos_(pos) {}
Object::Object(const Object & other) : id(count++), pos_(other.pos_) {}

Vector2 & Object::pos() { return pos_; }

int Object::count = 0;
