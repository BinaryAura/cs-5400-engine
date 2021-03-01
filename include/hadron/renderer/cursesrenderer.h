#ifndef CURSES_RENDERER_H
#define CURSES_RENDERER_H

#include <ncurses.h>
#include "hadron/renderer/renderer.h"

class CursesRenderer : public Renderer {
public:
  CursesRenderer() = default;
  virtual void clear(Window*) const override;
  virtual void on_update(Window*, TransformComponent&, SpriteComponent&) const override;
};

#endif // NCURSES_RENDERER_H
