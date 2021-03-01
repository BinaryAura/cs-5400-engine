#ifndef SCENE_H
#define SCENE_H


#include <entt.hpp>

#include "hadron/utility/log.h"
// #include "hadron/scene/entity.h"

class Window;
class Physics;
class Renderer;
class Application;
class Entity;

class Scene {
public:
  Scene() = default;
  ~Scene();

  Entity create_entity();

  bool is_valid(entt::entity& entity);

  void add_engine(Physics* engine) {
    this->engines.push_back(engine);
  }

  void add_renderer(Renderer* renderer) {
    this->renderers.push_back(renderer);
  }

  template<typename T>
  bool has_component(entt::entity& entity) {
    return this->registry.has<T>(entity);
  }

  template<typename T, typename ... Args>
  T& add_component(entt::entity& entity, Args&& ... args) {
    Log::get_core_logger()->trace("Adding component to Entity {}: {}", entity, typeid(T).name());
    return this->registry.emplace<T>(entity, std::forward<Args>(args) ...);
  }

  template<typename T>
  T& get_component(entt::entity& entity) {
    return this->registry.get<T>(entity);
  }

  template<typename T>
  T& remove_component(entt::entity& entity) {
    return this->registry.remove<T>(entity);
  }

  void destroy_entity(const entt::entity& entity) {
    this->registry.destroy(entity);
  }

  template<typename ... Owned, typename ... Get, typename ... Exclude>
  entt::basic_group<entt::entity, entt::exclude_t<Exclude ...>, entt::get_t<Get ...>, Owned ...> get_group(entt::get_t<Get ...>, entt::exclude_t<Exclude ...> = {}) {
    return this->registry.group<Owned ...>(entt::get_t<Get ...>{}, entt::exclude_t<Exclude ...>{});
  }

  Entity get_entity(const std::string&);

  template<typename ... T, typename Filter, typename ... Exclude>
  std::vector<Entity> filtered_view(Filter filter, entt::exclude_t<Exclude ...> = {}) {
    auto view = this->registry.view<T ...>();
    std::vector<Entity> fg;
    for(auto entity : view) {
      if(filter(Entity{entity, this})) {
        fg.emplace_back(entity, this);
      }
    }
    return fg;
  }

  template<typename Filter, typename ... Owned, typename ... Get, typename ... Exclude>
  std::vector<Entity> filtered_group(Filter filter, entt::get_t<Get ...>, entt::exclude_t<Exclude ...>) {
    auto group = this->registry.group<Owned ...>(entt::get_t<Get ...>{}, entt::exclude_t<Exclude ...>{});
    std::vector<Entity> fg;
    for(auto entity : group) {
      if(filter(Entity{entity, this})) {
        fg.emplace_back(entity, this);
      }
    }
    return fg;
  }

  void clear();

  void on_input(Application*);

  void on_update();

  void on_render(Window* window);

private:
  entt::registry registry;
  std::vector<Renderer*> renderers;
  // CursesRenderer* curses_renderer;
  std::vector<Physics*> engines;
  // TilePhysics* tile_engine;
};

#endif // SCENE_H
