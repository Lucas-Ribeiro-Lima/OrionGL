#pragma once

#include <Material.h>
#include <Mesh.h>
#include <Model.h>
#include <Program.h>
#include <Shader.h>
#include <Texture.h>
#include <memory.h>

namespace oriongl::core::storage {
// ======================================================
// Managers
// ======================================================

class ShaderManager {
  public:
    static std::shared_ptr<graphics::Program> getProgram(std::string vertex_src, std::string frag_src,
                                                         std::vector<std::string> defines = {});
};

// ------------------------------------------------------

class MeshManager {
  public:
    static std::shared_ptr<graphics::Mesh> getMesh(std::string mesh_path);
};

// ------------------------------------------------------

class TextureManager {
  public:
    static std::shared_ptr<graphics::Texture> getTexture(std::string tex_path);
};

// ------------------------------------------------------

class ModelManager {
  public:
    static std::shared_ptr<graphics::Model> getModel(std::shared_ptr<graphics::Program> shader, std::shared_ptr<graphics::Mesh> mesh,
                                  std::vector<std::string> textures);

    static std::shared_ptr<graphics::Model> getModel(std::shared_ptr<graphics::Program> shader, std::string &path);
};

// ======================================================
// Mesh Loader Helpers
// ======================================================

class MeshLoaderHelper {
  public:
    static std::shared_ptr<graphics::Mesh> getCubeMesh(float side_size);

    static std::shared_ptr<graphics::Mesh> getSphereMesh(float radius);
};

}; // namespace oriongl::core::storage
