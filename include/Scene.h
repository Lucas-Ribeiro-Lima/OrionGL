#pragma once

#include <Camera.h>
#include <Entity.h>

namespace oriongl::core {

struct Scene {
    std::vector<Entity> data;
    graphics::Light light;
    Camera camera;
};

}
