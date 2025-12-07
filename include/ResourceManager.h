#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"
#include "Program.h"
#include "Material.h"

#include <memory>

namespace oriongl::ecs {
    camera::Camera &getCamera();

    core::Mesh &getCubeData();

    std::shared_ptr<core::Mesh> getSphereData(float radius);

    std::shared_ptr<core::Texture> getTextureData(const char *tex);

    std::shared_ptr<core::Program> getProgram(const char *vertex, const char *frag);

    std::shared_ptr<core::Material> getMaterial(core::MaterialData &mat);

    constexpr std::pair<core::vertex_array, core::indexes_array> generateSphereRadiusVector(float radius);
}
