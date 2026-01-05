#include <PlanetRenderer.h>
#include <Renderer.h>
#include <Window.h>

int main() {
    oriongl::graphics::Window window{ "OrionGL-Sample" };
    oriongl::samples::solar_system::PlanetRenderer renderer{};

    window.linkRenderer(&renderer);
    window.render();
    return 0;
}
