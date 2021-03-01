#include <math.h>

#include "hadron/physics/tilephysics.h"

void TilePhysics::on_update(Scene &scene, TransformComponent& transform, MobileComponent& mobile, ColliderComponent& collider) {
  Log::get_core_logger()->trace("Physics on_update()");
  auto coll = (TileColliderComponent&)collider;
  auto tm = (TileMoveComponent&)mobile;
  if(glm::vec3(transform).x == tm.x && glm::vec3(transform).y == tm.y) {
    return; // Not moving
  }
  Log::get_core_logger()->trace("({}, {}) -> ({}, {})", glm::vec3(transform).x, glm::vec3(transform).y, tm.x, tm.y);
  Log::get_core_logger()->trace("Collider: solid({}), fills_tile({})", coll.solid, coll.fills_tile);

  auto group = scene.get_group<TileColliderComponent>(entt::get_t<TransformComponent>{});
  group.sort<TransformComponent>([transform](const auto& lhs, const auto& rhs)->bool{
    return abs(glm::vec3(lhs).x - glm::vec3(transform).x) + abs(glm::vec3(lhs).y - glm::vec3(transform).y) < abs(glm::vec3(rhs).x - glm::vec3(transform).x) + abs(glm::vec3(rhs).y - glm::vec3(transform).y);
  });

  for(auto entity : group) {
    auto [c, t] = group.get(entity);
    Log::get_core_logger()->trace("({}, {}), s: {}, f: {}", glm::vec3(t).x, glm::vec3(t).y, c.solid, c.fills_tile);
    if (abs(glm::vec3(t).x - glm::vec3(transform).x) + abs(glm::vec3(t).y - glm::vec3(transform).y) > abs(tm.x - glm::vec3(transform).x) + abs(tm.y - glm::vec3(transform).y)) {
      break; // sorted list distance is too far now, break
    } else if (glm::vec3(t).x == tm.x && glm::vec3(t).y == tm.y && coll.solid && c.solid && (coll.fills_tile || c.fills_tile) ) {
      Log::get_core_logger()->trace("Collided");
      return; // Can't move to (tm.x, tm.y)
    }
  }
  transform.transform = glm::vec3(((TileMoveComponent&)mobile).x, ((TileMoveComponent&)mobile).y, glm::vec3(transform).z);
}
