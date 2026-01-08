//
// Created by lucas.lima on 30/11/2025.
//
#pragma once
#include <Scene.h>

namespace oriongl::core {
class RenderSystem {
  public:
    RenderSystem ();
    void render(Scene &scene);
  };
} // namespace oriongl::core

