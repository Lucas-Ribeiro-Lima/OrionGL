#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "Model.h"

namespace oriongl::core {

struct Entity {
    std::shared_ptr<graphics::Model> model;
    std::vector<glm::vec3> instances;
};

} // namespace oriongl::core
