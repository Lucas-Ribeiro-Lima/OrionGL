#pragma once

#include <glad.h>
#include <GLFW/glfw3.h>

namespace oriongl::core {
class WindowSystem {
  public:
    WindowSystem();
    WindowSystem(const char *title);

    void swapBuffers();
    void closeWindow();
    void update();

  private:
    GLFWwindow *window = nullptr;
    GLFWmonitor *monitor = nullptr;
    const GLFWvidmode *vidmode = nullptr;
    const char *window_title = "Default title";
    int height = 920;
    int width = 1280;
    float deltaTime = 0;
    float lastFrame = 0;

    // Glad configuration;
    void gladConfiguration();

    // Window configuration
    void windowInicialization();

    void processInput(GLFWwindow *window);

    // GLFW start configuration
    void glfwConfiguration();

    void calculateDeltaTime();

    static void mouseCallback(GLFWwindow *window, double xPos, double yPos);

    static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
};
} // namespace oriongl::core
