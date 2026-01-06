#include <BoxesRenderer.h>
#include <Window.h>

int main() {
    oriongl::graphics::Window window{"Basic sample"};
    oriongl::samples::boxes::BoxesRenderer renderer;

    window.linkRenderer(&renderer);
    window.render();

    return 0;
}
