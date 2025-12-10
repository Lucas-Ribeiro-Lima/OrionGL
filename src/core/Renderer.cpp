//
// Created by lucas.lima on 30/11/2025.
//

#include <Renderer.h>
#include <ResourceManager.h>

namespace oriongl::core {
    Renderer::Renderer() : cam1(getCamera()) {}

    void Renderer::render() {
        for (auto &i: data) {
            i.drawInstances();
        }
    }

    Camera &Renderer::getMainCam() {
        return cam1;
    }
}
