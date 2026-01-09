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

    auto &light = scene.light;
    auto &camera = scene.camera;

    for (auto &entitie : scene.data) {

        auto &instances = entitie.instances;
        auto &model = entitie.model;

        auto shader = model->getModelProgram();

        shader->use();
        shader->setCamera(camera);
        shader->setLight(light);

        for (auto &instance : instances) {
            shader->resetModelMatrix();
            shader->translate(instance);
            shader->setModelMatrix();

            model->draw();
        };
    }
}
} // namespace oriongl::core
