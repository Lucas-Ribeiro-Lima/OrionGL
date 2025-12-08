#include "Window.h"
#include <stdexcept>

namespace oriongl::graphics {
    Window::Window(const char *title) : Window{} {
        this->window_title = title;
    }

    Window::Window() {
        glfwConfiguration();
        windowInicialization();
        gladConfiguration();
    }

    void Window::gladConfiguration() {
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            throw std::runtime_error("Failed to initialize GLAD");
        }

        glViewport(0, 0, vidmode->width, vidmode->height);
        glEnable(GL_DEPTH_TEST);
    }

    void Window::glfwConfiguration() {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    }

    void Window::windowInicialization() {
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

    void Window::initializeSystem(core::Renderer *system) {
        sys = system;
    }


    void Window::processInput(GLFWwindow *window) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            sys->getMainCam().setFrontBack(deltaTime, core::front);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            sys->getMainCam().setFrontBack(deltaTime, core::back);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            sys->getMainCam().setLeftRight(deltaTime, core::left);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            sys->getMainCam().setLeftRight(deltaTime, core::right);
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            sys->getMainCam().setUpDown(deltaTime, core::up);
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
            sys->getMainCam().setUpDown(deltaTime, core::down);
        }
    }

    void Window::render() {
        while (!glfwWindowShouldClose(window)) {
            calculateDeltaTime();

            processInput(window);

            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            sys->process();

            glfwSwapBuffers(window);

            glfwPollEvents();
        }

        glfwTerminate();
    }

    void Window::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    void Window::mouseCallback(GLFWwindow *window, double xPos, double yPos) {
        auto self = static_cast<Window *>(glfwGetWindowUserPointer(window));
        self->sys->getMainCam().update(xPos, yPos);
    }

    void Window::calculateDeltaTime() {
        auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }
}
