#include "hadron/scene/scene.h"
#include "hadron/scene/entity.h"
#include "hadron/scene/components.h"
#include "hadron/physics/physics.h"
#include "hadron/renderer/renderer.h"

// temporary
#include "hadron/scene/cursescomponents.h"

Scene::~Scene() {
  for(auto engine : this->engines) {
    delete engine;
  }
  for(auto renderer : this->renderers) {
    delete renderer;
  }
}

Entity Scene::create_entity() {
  auto entity = this->registry.create();
  Log::get_core_logger()->trace("Creating Entity: {}", entity);
  return {entity , this};
}

bool Scene::is_valid(entt::entity& entity) {
  return this->registry.valid(entity);
}

void Scene::clear() {
  this->registry.clear();
}

void Scene::on_input(Application* app) {
  // User Input
  // AIS
  Log::get_core_logger()->trace("on_input() call");
  auto group = this->registry.group<AIComponent>(entt::get<TransformComponent, TileMoveComponent, TagComponent, TurnComponent>);
  group.sort<TurnComponent>([](auto &lhs, auto &rhs){
    return lhs.number < rhs.number;
  });
  for(auto entity : group) {
    auto [ai, transform, move, tag, turn] = group.get(entity);
    Log::get_core_logger()->trace("AI for {} @ ({}, {})", tag.name, glm::vec3(transform).x, glm::vec3(transform).y);
    ai.action(app, {entity, this});
    // Log::get_core_logger()->info("x({}) -> {}, y({}) -> {}", transform.x, move.x, transform.y, move.y);
  }
}

void Scene::on_update() {
  // Physics
  // Board Moves
  Log::get_core_logger()->trace("on_update() call");
  auto group = this->registry.group<TileMoveComponent>(entt::get<TransformComponent, TileColliderComponent, TagComponent>);
  for(auto entity : group) {
    auto [move, transform, collider, tag] = group.get(entity);
    Log::get_core_logger()->trace("TilePhysics for {} @ ({}, {})", tag.name, glm::vec3(transform).x, glm::vec3(transform).y);
    for(auto &engine : this->engines) {
      engine->on_update(*this, transform, (MobileComponent&)move, (ColliderComponent&)collider);
    }
  }
}

void Scene::on_render(Window* window) {
  // Update Animations
  // Buffers are not swapped here!
  Log::get_core_logger()->trace("on_render() call");
  for(auto &renderer : this->renderers) {
    renderer->clear(window);
  }
  auto group = this->registry.group<CursesSpriteComponent>(entt::get<TransformComponent, TagComponent>);
  group.sort<TransformComponent>([](const auto& lhs, const auto& rhs)->bool{
    return glm::vec3(lhs).z < glm::vec3(rhs).z;
  });
  for(auto entity : group) {
    auto [sprite, transform, tag] = group.get(entity);
    Log::get_core_logger()->trace("CursesRender for {} @ ({}, {})", tag.name, glm::vec3(transform).x, glm::vec3(transform).y);
    for(auto &renderer : this->renderers) {
      renderer->on_update(window, transform, (SpriteComponent&)sprite);
    }
  }
}

Entity Scene::get_entity(const std::string& name) {
  auto view = this->registry.view<TagComponent>();
  for(auto entity : view) {
    auto &tag = view.get<TagComponent>(entity);
    if(tag.name == name)
      return {entity, this};
  }
  return Entity();
}
