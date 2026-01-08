#pragma once

#include <Camera.h>
#include <Entity.h>

namespace oriongl::core {

struct Scene {
    std::vector<Entity> data;
    std::vector<graphics::Light> lights;
    Camera camera;
};

}
