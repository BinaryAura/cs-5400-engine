#ifndef CURSES_COMPONENTS_H
#define CURSES_COMPONENTS_H

#include <ncurses.h>
#include "hadron/scene/components.h"

struct CursesSpriteComponent : public SpriteComponent {
  CursesSpriteComponent() = default;
  CursesSpriteComponent(const CursesSpriteComponent&) = default;
  CursesSpriteComponent(const chtype sprite, const bool visible) : SpriteComponent(visible), sprite(sprite) {}
  // Todo: color
  chtype sprite;
};

#endif // CURSES_COMPONENTS_H
