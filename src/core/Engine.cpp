
#include <Engine.h>

namespace oriongl {

void Engine::run() {
    status = ENGINE_RUNNING;
    while (status == ENGINE_RUNNING) {
        windowSystem.update();
        renderSystem.render(scene);
        windowSystem.swapBuffers();
    }

    windowSystem.closeWindow();
}

void Engine::loadEntityToScene(std::shared_ptr<graphics::Model> model, std::vector<glm::vec3> instances) {
    core::Entity entity;
    entity.model = std::move(model);
    entity.instances = instances;
    scene.data.push_back(std::move(entity));
}

} // namespace oriongl
