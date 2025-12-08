#include <PlanetRenderer.h>
#include <Renderer.h>
#include <Window.h>

int main() {
    oriongl::graphics::Window window{ "OrionGL-Sample" };
    oriongl::samples::PlanetRenderer renderer{};

    window.initializeSystem(&renderer);
    window.render();
    return 0;
}
