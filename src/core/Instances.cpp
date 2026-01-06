#include "Instances.h"

namespace oriongl::core {
Instances::Instances(std::unique_ptr<graphics::Model> obj) : obj(std::move(obj)) {};

void Instances::drawInstances() {
    for (auto &instance : instances) {
        (*obj).setTranslate(instance->position).setScale(instance->scale_axis).setRotate(instance->rotate_deg, instance->rotate_axis).draw();
    }
}

void Instances::addInstance(graphics::ModelData inst) { instances.emplace_back(std::make_shared<graphics::ModelData>(inst)); }

void Instances::deleteInstance(size_t index) { instances.erase(instances.begin() + index); }
} // namespace oriongl::core
