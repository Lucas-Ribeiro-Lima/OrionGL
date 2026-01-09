#pragma once

#include <WindowSystem.h>
#include <RenderSystem.h>
#include <ResourceSystem.h>
#include <Scene.h>

namespace oriongl {

enum EngineStatus {
    ENGINE_RUNNING,
    ENGINE_CLOSING,
    ENGINE_STOPPED,
};

class Engine {
  private:
    core::WindowSystem windowSystem;
    core::ResourceSystem resourceSystem;
    core::RenderSystem renderSystem;

    core::Scene scene;
    EngineStatus status = ENGINE_STOPPED;

  public:
    Engine() = default;
    void run();
    void loadEntityToScene(std::shared_ptr<graphics::Model> model, std::vector<glm::vec3> instances);
};

} // namespace oriongl
