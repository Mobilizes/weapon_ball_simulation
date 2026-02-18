#ifndef ATTACHABLE_OBJECT_HPP
#define ATTACHABLE_OBJECT_HPP

#include "weapon_ball/objects/object.hpp"

#include <memory>

class AttachableObject : private Object
{
public:
  AttachableObject(Vector2 pos);
  AttachableObject(Vector2 pos, std::shared_ptr<Object> parent);

  Vector2 pos();
  Vector2 & relative_pos();

protected:
  std::shared_ptr<Object> parent = nullptr;

private:
  Vector2 relative_pos_;
};

#endif  // ATTACHABLE_OBJECT_HPP
