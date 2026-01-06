#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "Model.h"

namespace oriongl::core {
typedef std::vector<std::shared_ptr<graphics::ModelData>> instances_data; 

class Instances {
    std::unique_ptr<graphics::Model> obj;
    instances_data instances;

  public:
    Instances(std::unique_ptr<graphics::Model> obj);

    void addInstance(graphics::ModelData inst);

    void deleteInstance(size_t index);

    void drawInstances();
};
} // namespace oriongl::core
