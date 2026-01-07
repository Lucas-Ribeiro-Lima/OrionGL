#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "Material.h"
#include "Mesh.h"
#include "Program.h"

namespace oriongl::graphics {
using uint = unsigned int;
typedef glm::vec3 model_vector;

typedef model_vector ModelPosition;
typedef model_vector ModelScaleAxis;
typedef model_vector ModelRotateAxis;
typedef float ModelRotateDeg;

struct ModelData {
    ModelPosition position{0.0f};
    ModelScaleAxis scale_axis{1.0f};
    ModelRotateAxis rotate_axis{1.0f};
    ModelRotateDeg rotate_deg{0.0f};
};

class Model {
  protected:
    ModelData data{};

    std::vector<std::shared_ptr<Mesh>> meshes;
    std::vector<std::shared_ptr<Material>> materials;
    std::shared_ptr<Program> program = nullptr;

    void saveBuffer();

    void genVertexArrayBuffer();

    void bindGeometry() const;

    void bindTexture() const;

  public:
    Model(std::shared_ptr<Program> program);

    virtual ~Model() = default;

    void loadData(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material = nullptr);
    void deleteData(size_t index);

    std::shared_ptr<Program> getModelProgram() const;

    Model &setProgram(std::shared_ptr<Program> prg);

    Model &setTranslate(glm::vec3 axis);

    Model &setRotate(float deg, glm::vec3 axis);

    Model &setScale(glm::vec3 axis);

    virtual void draw();
};
} // namespace oriongl::graphics
