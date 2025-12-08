#include <Window.h>
#include <System.h>

int main() {
    oriongl::graphics::Window window{ "OrionGL" };
    oriongl::core::PlanetSystem system{};

    window.initializeSystem(&system);
    window.render();
    return 0;
}
