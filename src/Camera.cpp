#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace oriongl::camera {
    Camera::Camera() {
    };

    void Camera::setFrontBack(float value, Directions dir) {
        if (dir == 1) pos += front * cameraSpeed * value;
        else pos -= front * cameraSpeed * value;
        updateView();
    }

    void Camera::setLeftRight(float value, Directions dir) {
        if (dir == 1) pos += glm::normalize(glm::cross(front, up)) * cameraSpeed * value;
        else pos -= glm::normalize(glm::cross(front, up)) * cameraSpeed * value;
        updateView();
    }

    void Camera::setUpDown(float value, Directions dir) {
        if (dir == 1) pos += up * cameraSpeed * value;
        else pos -= up * cameraSpeed * value;
        updateView();
    }

    glm::mat4 Camera::getView() {
        return view;
    }

    glm::mat4 Camera::getPerspective() {
        return perspective;
    }

    glm::vec3 Camera::getViewPosition() {
        return pos;
    }

    void Camera::updateView() {
        view = glm::lookAt(pos, pos + front, up);
    }

    void Camera::updatePerspective() {
        perspective = glm::perspective(45.0f, 1280.0f / 960.0f, 0.1f, 300.0f);
    }

    void Camera::update(float x, float y) {
        if (firstMouse) {
            lastX = x;
            lastY = y;
            firstMouse = false;
            return;
        }

        float deltaYaw = (x - lastX) * sensitivity;
        float deltaPitch = (lastY - y) * sensitivity;

        if (deltaPitch == 0 && deltaYaw == 0) return;

        yaw += deltaYaw;
        pitch += deltaPitch;

        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(
                          glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(
            glm::radians(pitch));
        direction.z = sin(
                          glm::radians(yaw)) * cos(glm::radians(pitch));

        front = glm::normalize(direction);
        lastX = x;
        lastY = y;

        updateView();
    }
}
