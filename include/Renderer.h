//
// Created by lucas.lima on 30/11/2025.
//

#ifndef OPENGL_LEARNING_SYSTEM_H
#define OPENGL_LEARNING_SYSTEM_H

#include <Camera.h>
#include <Instances.h>
#include <vector>

namespace oriongl::core {
class Renderer {
    Camera &cam1;

  protected:
    std::vector<Instances> data;

  public:
    Renderer();
    virtual ~Renderer() = default;

    virtual void render();
    virtual Camera &getMainCam();
};
} // namespace oriongl::core

#endif // OPENGL_LEARNING_SYSTEM_H
