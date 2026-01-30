#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <raylib.h>

class Object
{
public:
  Object();
  Object(const Object & other);

  virtual void update(float dt) = 0;
  virtual void draw() = 0;

  int id;

private:
  static int count;
};

#endif  // OBJECT_HPP
