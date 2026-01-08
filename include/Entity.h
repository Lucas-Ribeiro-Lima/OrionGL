#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "Model.h"

namespace oriongl::core {
typedef std::vector<float[3]> instances_data;

struct Entity {
    std::unique_ptr<graphics::Model> model;
    instances_data instances;
}; // namespace oriongl::core

} // namespace oriongl::core
