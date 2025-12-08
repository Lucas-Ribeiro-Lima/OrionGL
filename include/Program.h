#pragma once

#include <glm/glm.hpp>

#include "Light.h"
#include "Camera.h"
#include "Shader.h"

namespace oriongl::graphics {
    class Program {
        char infoLog[512] = {};
        Light light;
        core::Camera &cam;

        glm::mat4 projection = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::vec3 viewPos = glm::vec3(0.0f);

        int sucess = 0;
        unsigned int ID = 0;

    public:
        Program(Shader&& vertex, Shader&& fragment);

        Program &resetT();

        Program &scale(glm::vec3 scaleProps);

        Program &rotate(float degree, glm::vec3 rotateProps);

        Program &translate(glm::vec3 translateProps);

        void setCommonUniforms();

        void setUniform1I(const char name[], int value) const;

        void setUniform1UI(const char name[], int value) const;

        void setUniform1f(const char name[], float value) const;

        void setUniform3fv(const char name[], glm::vec3 &vec);

        void setUniform4fv(const char name[], glm::mat4 &mat);

        void setUniform1i(const char name[], int value);

        void use();

        void errors();
    };
}
