#ifndef RENDERER_H
#define RENDERER_H

#include "hadron/window/window.h"
#include "hadron/scene/components.h"

class Renderer {
public:
  Renderer() = default;
  virtual ~Renderer() = default;
  virtual void clear(Window*) const = 0;
  virtual void on_update(Window*, TransformComponent&, SpriteComponent&) const = 0;
};

#endif // RENDERER_H
