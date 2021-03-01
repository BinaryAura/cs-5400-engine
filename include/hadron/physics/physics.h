#ifndef PHYSICS_H
#define PHYSICS_H

#include "hadron/scene/components.h"

class Physics {
public:
  virtual ~Physics() = default;

  virtual void on_update(Scene&, TransformComponent&, MobileComponent&, ColliderComponent&) = 0;
};

#endif // PHYSICS_H
