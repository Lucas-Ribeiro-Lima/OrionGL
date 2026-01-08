//
// Created by lucas.lima on 30/11/2025.
//

#ifndef OPENGL_LEARNING_SYSTEM_H
#define OPENGL_LEARNING_SYSTEM_H

#include <Scene.h>

namespace oriongl::core {
class RenderSystem {
  public:
    RenderSystem ();
    void render(Scene &scene);
  };
} // namespace oriongl::core

#endif // OPENGL_LEARNING_SYSTEM_H
