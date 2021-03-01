#include "hadron/renderer/cursesrenderer.h"
#include "hadron/scene/cursescomponents.h"
#include "hadron/utility/log.h"

using RawCursesWindow = WINDOW;

void CursesRenderer::clear(Window* window) const {
  Log::get_core_logger()->trace("Clear Window");
  werase((RawCursesWindow*)window->get_native_window());
}

void CursesRenderer::on_update(Window* window, TransformComponent& transform, SpriteComponent& sprite) const {
  Log::get_core_logger()->trace("Sprite: ({},{}), visible? {}", glm::vec3(transform).x, glm::vec3(transform).y, sprite.visible);
  if(sprite.visible) {
    mvwaddch((RawCursesWindow*)window->get_native_window(), glm::vec3(transform).y, glm::vec3(transform).x, ((CursesSpriteComponent&)sprite).sprite);
  }
}
