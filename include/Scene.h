#pragma once

#include <Camera.h>
#include <Instances.h>

namespace oriongl::core {

struct Scene {
    std::vector<Instances> data;
    std::vector<graphics::Light> lights;
    Camera camera;
};

}
