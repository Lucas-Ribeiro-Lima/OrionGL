//
// Created by lucas.lima on 30/11/2025.
//

#include <RenderSystem.h>
#include <ResourceManager.h>

namespace oriongl::core {
    RenderSystem::RenderSystem() {}

    void RenderSystem::render(Scene &scene) {
      auto& lights = scene.lights;
      auto& camera = scene.camera;

      for(auto& actor : scene.data) {
          actor.drawInstances(); 
      }
    }
}
