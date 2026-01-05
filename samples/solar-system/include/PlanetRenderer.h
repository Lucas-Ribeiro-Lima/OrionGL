//
// Created by lucas.lima on 08/12/2025.
//

#ifndef ORIONGL_PLANETRENDERER_H
#define ORIONGL_PLANETRENDERER_H

#include <Renderer.h>

namespace oriongl::samples::solar_system {
    class PlanetRenderer : public core::Renderer {
        std::vector<core::Instances> stars;
        std::vector<core::Instances> planets;
        core::Camera &cam1;

        void loadData();

    public:
        PlanetRenderer();

        void render() override;

        ~PlanetRenderer() override = default;

        core::Camera &getMainCam() override;
    };
}

#endif //ORIONGL_PLANETRENDERER_H
