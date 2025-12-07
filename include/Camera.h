#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace oriongl::camera {
    enum Directions {
        up = 1,
        front = 1,
        right = 1,
        left = -1,
        back = -1,
        down = -1
    };

    class Camera {
        glm::vec3 pos{0.0f, 0.0f, 30.0f};
        glm::vec3 front{0.0f, 0.0f, -1.0f};
        glm::vec3 up{0.0f, 1.0f, 0.0f};

        glm::mat4 view = glm::lookAt(pos, pos + front, up);
        glm::mat4 perspective = glm::perspective(45.0f, 1280.0f / 920.0f, 0.1f, 1000.f);

        float cameraSpeed = 50.0f;

        float fov = 45.0f;
        float yaw = -90.0f;
        float pitch = 0.0f;

        float lastX;
        float lastY;

        float sensitivity = 0.1f;

        bool firstMouse = true;

    public:
        Camera();

        glm::mat4 getView();

        glm::mat4 getPerspective();

        glm::vec3 getViewPosition();

        void updateView();

        void updatePerspective();

        void update(float x, float y);

        void setFrontBack(float value, Directions dir);

        void setLeftRight(float value, Directions dir);

        void setUpDown(float value, Directions dir);
    };
}
