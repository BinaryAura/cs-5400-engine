#ifndef TILE_PHYSICS_H
#define TILE_PHYSICS_H

#include "hadron/physics/physics.h"

class TilePhysics : public Physics {
public:
  void on_update(Scene&, TransformComponent&, MobileComponent&, ColliderComponent&);
};

#endif // TILE_PHYSICS_H
