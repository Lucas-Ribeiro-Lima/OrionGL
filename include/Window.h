#pragma once
#include <glad.h>
#include <GLFW/glfw3.h>
#include <System.h>

namespace oriongl::render {
    class Window {
    public:
        Window();
        void render();
        void initializeSystem(ecs::System* sys);
        int hasErrors() const;

    private:
        GLFWwindow *window = nullptr;
        GLFWmonitor *monitor = nullptr;
        const GLFWvidmode *vidmode = nullptr;
        ecs::System* sys = nullptr;
        int height = 920;
        int width = 1280;
        int errors;
        float deltaTime = 0;
        float lastFrame = 0;

        //Glad configuration;
        void gladConfiguration();

        //Window configuration
        void windowInicialization();

        void processInput(GLFWwindow *window);

        //GLFW start configuration
        void glfwConfiguration();

        void calculateDeltaTime();

        static void mouseCallback(GLFWwindow *window, double xPos, double yPos);
        static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
    };
}