#include "weapon_ball/objects/object.hpp"

Object::Object(Vector2 pos) : id(count++), pos(pos) {}
Object::Object(const Object & other) : id(count++), pos(other.pos) {}

int Object::count = 0;
