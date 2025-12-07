#include <Window.h>
#include <System.h>

int main() {
    oriongl::render::Window window{ "OrionGL" };
    oriongl::ecs::PlanetSystem system{};

    window.initializeSystem(&system);
    window.render();
    return 0;
}
