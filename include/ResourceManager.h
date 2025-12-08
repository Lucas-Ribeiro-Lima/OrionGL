#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"
#include "Program.h"
#include "Material.h"

#include <memory>

namespace oriongl::core {
    Camera &getCamera();

    graphics::Mesh &getCubeData();

    std::shared_ptr<graphics::Mesh> getSphereData(float radius);

    std::shared_ptr<graphics::Texture> getTextureData(const char *tex);

    std::shared_ptr<graphics::Program> getProgram(const char *vertex, const char *frag);

    std::shared_ptr<graphics::Material> getMaterial(graphics::MaterialData &mat);

    constexpr std::pair<graphics::vertex_array, graphics::indexes_array> generateSphereRadiusVector(float radius);
}
