#pragma once

#include <ResourceSystem.h>

namespace oriongl {

class Engine {
    core::ResourceSystem resourceSystem;

  public:
    Engine();
    void start();
    void stop();
};

} // namespace oriongl
