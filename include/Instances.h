#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include "Model.h"

typedef  std::shared_ptr<glm::vec3> model_position;
typedef  std::vector<model_position> instances_positions;

class Instances {
    std::unique_ptr<Model> obj;
    instances_positions pos;

public:
    Instances(std::unique_ptr<Model> obj);

    void addInstance(const model_position &inst);

    void deleteInstance(size_t index);

    void drawInstances();
};
