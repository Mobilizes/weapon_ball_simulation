#include "weapon_ball/object.hpp"

Object::Object() { id = count++; }
Object::Object(const Object & other) { id = count++; }

int Object::count = 0;
