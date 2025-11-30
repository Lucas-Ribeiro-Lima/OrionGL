#include <Window.h>
#include <System.h>

int main() {
    Window window{};
    PlanetSystem system{};

    window.initializeSystem(&system);

    if (window.hasErrors()) return -1;

    window.render();
    return 0;
}
