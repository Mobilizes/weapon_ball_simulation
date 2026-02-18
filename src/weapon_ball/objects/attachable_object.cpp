#include "weapon_ball/objects/attachable_object.hpp"

#include "raymath.h"

AttachableObject::AttachableObject(Vector2 pos) : relative_pos_(pos) {}

AttachableObject::AttachableObject(Vector2 pos, std::shared_ptr<Object> parent)
: relative_pos_(pos), parent(parent)
{
}

Vector2 AttachableObject::pos()
{
  return relative_pos() + (parent ? parent->pos() : Vector2Zero());
}

Vector2 & AttachableObject::relative_pos() { return relative_pos_; }
