#include "Instances.h"

namespace oriongl::ecs {
    Instances::Instances(std::unique_ptr<core::Model> obj) : obj(std::move(obj)) {
    };

    void Instances::drawInstances() {
        for (int i = 0; i < pos.size(); i++) {
            (*obj)
                    .setTranslate(*pos[i])
                    .draw();
        }
    }

    void Instances::addInstance(model_position inst) {
        pos.push_back(std::move(inst));
    }

    void Instances::deleteInstance(size_t index) {
        pos.erase(pos.begin() + index);
    }
}
