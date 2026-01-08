//
// Created by lucas.lima on 30/11/2025.
//

#include <RenderSystem.h>
#include <glad.h>

namespace oriongl::core {
RenderSystem::RenderSystem() {}

void RenderSystem::render(Scene &scene) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto &lights = scene.lights;
    auto &camera = scene.camera;

    for (auto &entitie : scene.data) {
    }
}
} // namespace oriongl::core
