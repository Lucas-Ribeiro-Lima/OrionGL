#pragma once

#include "Camera.h"
#include "Material.h"
#include "Mesh.h"
#include "Program.h"
#include "Texture.h"

#include <memory>

namespace oriongl::core {
Camera &getCamera();

std::shared_ptr<graphics::Mesh> getCubeData(float side_size);

std::shared_ptr<graphics::Mesh> getSphereData(float radius);

std::shared_ptr<graphics::Texture> getTextureData(std::string tex);

std::shared_ptr<graphics::Program> getProgram(std::string vertex_src_path, std::string frag_src_path, std::vector<std::string> defines = {});

std::shared_ptr<graphics::Program> getProgram(const char *vertex_src_path, const char *frag_src_path, std::vector<std::string> defines = {});

std::shared_ptr<graphics::Material> getMaterial(graphics::MaterialData &mat);

constexpr std::pair<graphics::vertex_array, graphics::indexes_array> generateSphereRadiusVector(float radius);
} // namespace oriongl::core
