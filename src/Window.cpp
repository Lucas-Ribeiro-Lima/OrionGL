#include "Window.h"
#include "Utils.h"

enum ERRORS {
  NONE = 0b0000,
  FAIL_CREATE_WINDOW = 0b0001,
  FAIL_INIT_GLAD = 0b0010,
};

Window::Window() {
  errors = NONE;

  glfwConfiguration();

  windowInicialization();
  if ((errors & FAIL_CREATE_WINDOW) == FAIL_CREATE_WINDOW) return;

  gladConfiguration();
  if ((errors & FAIL_INIT_GLAD) == FAIL_INIT_GLAD) return;
}

void Window::gladConfiguration() {
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    Utils::logger("Failed to initialize GLAD");
    errors = FAIL_INIT_GLAD;
    return;
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

  GLFWwindow *w = glfwCreateWindow(vidmode->width, vidmode->height, "LearnOpenGL", nullptr, nullptr);
  glfwSetWindowUserPointer(w, this);
  window = w;

  if (window == nullptr) {
    Utils::logger("Failed to create GLFW window");
    errors = FAIL_CREATE_WINDOW;
    glfwTerminate();
    return;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(window, mouseCallback);
}

void Window::initializeSystem(System* system) {
  sys = system;
}


void Window::processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    sys->getMainCam().setFrontBack(deltaTime, front);
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    sys->getMainCam().setFrontBack(deltaTime, back);
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    sys->getMainCam().setLeftRight(deltaTime, left);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    sys->getMainCam().setLeftRight(deltaTime, right);
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    sys->getMainCam().setUpDown(deltaTime, up);
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
    sys->getMainCam().setUpDown(deltaTime, down);
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

int Window::hasErrors() const {
  return (errors & (FAIL_CREATE_WINDOW | FAIL_INIT_GLAD)) > 0;
}

void Window::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void Window::mouseCallback(GLFWwindow *window, double xPos, double yPos) {
  auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
  self->sys->getMainCam().update(xPos, yPos);
}

void Window::calculateDeltaTime() {
  auto currentFrame = static_cast<float>(glfwGetTime());
  deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;
}
