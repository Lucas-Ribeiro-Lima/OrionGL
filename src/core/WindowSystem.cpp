#include <WindowSystem.h>
#include <stdexcept>


namespace oriongl::core {
WindowSystem::WindowSystem(const char *title) : WindowSystem() { this->window_title = title; }

WindowSystem::WindowSystem() {
    glfwConfiguration();
    windowInicialization();
    gladConfiguration();
}

void WindowSystem::gladConfiguration() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glViewport(0, 0, vidmode->width, vidmode->height);
    glEnable(GL_DEPTH_TEST);
}

void WindowSystem::glfwConfiguration() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
}

void WindowSystem::windowInicialization() {
    monitor = glfwGetPrimaryMonitor();
    vidmode = glfwGetVideoMode(monitor);

    GLFWwindow *w = glfwCreateWindow(vidmode->width, vidmode->height, this->window_title, nullptr, nullptr);
    glfwSetWindowUserPointer(w, this);
    window = w;

    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouseCallback);
}

void WindowSystem::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void WindowSystem::swapBuffers() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void WindowSystem::update() {
    calculateDeltaTime();
    processInput(window);
}

void WindowSystem::closeWindow() { glfwTerminate(); }

void WindowSystem::framebufferSizeCallback(GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); }

void WindowSystem::mouseCallback(GLFWwindow *window, double xPos, double yPos) {
    auto self = static_cast<WindowSystem *>(glfwGetWindowUserPointer(window));
}

void WindowSystem::calculateDeltaTime() {
    auto currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}
} // namespace oriongl::core
