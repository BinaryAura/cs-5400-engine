#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <glm/glm.hpp>

#include "hadron/scene/entity.h"

class Scene;

// class Scene;

// Required Components

struct TransformComponent {
  TransformComponent() = default;
  TransformComponent(const TransformComponent&) = default;
  TransformComponent(const glm::vec3& transform) : transform(transform), rotation(0.0f) {}
  TransformComponent(const float x, const float y, const float z) : transform(glm::vec3(x, y, z)), rotation(glm::vec3(0.0f, 0.0f, 0.0f)) {}

  operator glm::vec3& () { return this->transform; }
  operator const glm::vec3& () const { return this->transform; }

  glm::vec3 transform{0.0f, 0.0f, 0.0f};
  glm::vec3 rotation{0.0f, 0.0f, 0.0f};
};

struct TagComponent {
  TagComponent() = default;
  TagComponent(const TagComponent&) = default;
  TagComponent(const std::string& name) : name(name) {};

  operator const std::string& () const { return this->name; }

  std::string name;
};

// Base Components

struct SpriteComponent {
  SpriteComponent() = default;
  SpriteComponent(const SpriteComponent&) = default;
  SpriteComponent(const bool visible) : visible(visible) {}

  bool visible = true;
};

struct ColliderComponent {
  ColliderComponent() = default;
  ColliderComponent(const ColliderComponent&) = default;
  ColliderComponent(const bool solid) : solid(solid) {}

  bool solid = true;
};

struct MobileComponent {
  MobileComponent() = default;
  MobileComponent(const MobileComponent&) = default;
};

// Grid World Components

struct TileMoveComponent : public MobileComponent {
  TileMoveComponent() = default;
  TileMoveComponent(const TileMoveComponent&) = default;
  TileMoveComponent(const uint32_t x, const uint32_t y): x(x), y(y) {}

  uint32_t x;
  uint32_t y;
};

struct TileColliderComponent : public ColliderComponent {
  TileColliderComponent() = default;
  TileColliderComponent(const TileColliderComponent&) = default;
  TileColliderComponent(const bool solid, const bool fills_tile) : ColliderComponent(solid), fills_tile(fills_tile) {}

  bool fills_tile;
};

struct TileMapComponent {
  TileMapComponent() = default;
  TileMapComponent(const TileMapComponent&) = default;
  TileMapComponent(const uint32_t rows, const uint32_t cols, const uint32_t cell_width = 1, const uint32_t cell_height = 1) : rows(rows), cols(cols), cell_width(cell_width), cell_height(cell_height) {}

  uint32_t distance(const TransformComponent& lhs, const TransformComponent& rhs) const {
    return std::sqrt(std::pow(glm::vec3(lhs).x - glm::vec3(rhs).x, 2) + std::pow(glm::vec3(lhs).y - glm::vec3(rhs).y, 2));
  }

  std::vector<TransformComponent> get_neighbors(TransformComponent& transform) const {
    return {{glm::vec3(transform).x,glm::vec3(transform).y - 1, 0},
    {glm::vec3(transform).x + 1, glm::vec3(transform).y, 0},
    {glm::vec3(transform).x, glm::vec3(transform).y + 1, 0},
    {glm::vec3(transform).x - 1, glm::vec3(transform).y, 0}};
  }

  std::vector<Entity> get_entities(Scene& scene, const TransformComponent& transform) const {
    return scene.filtered_view<TransformComponent>([transform](Entity entity){
      auto& t = entity.get_component<TransformComponent>();
      return glm::vec3(t).x == glm::vec3(transform).x && glm::vec3(t).y == glm::vec3(transform).y;
    });
  }

  uint32_t cell_width;
  uint32_t cell_height;
  uint32_t cols;
  uint32_t rows;
};

// Artificial intelligence

struct AIComponent {
  AIComponent() = default;
  AIComponent(const AIComponent&) = default;

  AIComponent(void (* const action)(Application*, Entity)) : action(action) {}
  void (*action)(Application *, Entity);
};

// User Input

struct InputComponent {
  InputComponent() = default;
  InputComponent(const InputComponent&) = default;

  InputComponent(void (* const action)(Application*, Entity)) : action(action) {}
  void (*action)(Application*, Entity);
};

// Enforce physics order
struct TurnComponent {
  TurnComponent() = default;
  TurnComponent(const TurnComponent&) = default;
  TurnComponent(const uint32_t number) : number(number) {}

  uint32_t number;
};

#endif // COMPONENTS_H
