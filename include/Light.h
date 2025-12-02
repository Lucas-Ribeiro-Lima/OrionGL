//
// Created by lucas.lima on 10/09/2025.
//

#ifndef OPENGL_LEARNING_LIGHT_H
#define OPENGL_LEARNING_LIGHT_H

#include "glm/vec3.hpp"

struct Light {
    glm::vec3 position{ 0.0f };
    glm::vec3 ambient{ 0.05f };
    glm::vec3 diffuse{0.8f};
    glm::vec3 specular{1.0f};
};


#endif //OPENGL_LEARNING_LIGHT_H