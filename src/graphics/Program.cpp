#include "Program.h"
#include "Shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include <glad.h>

namespace oriongl::graphics {
Program::Program(Shader &&vertex, Shader &&fragment) {
    ID = glCreateProgram();
    glAttachShader(ID, vertex.getId());
    glAttachShader(ID, fragment.getId());
    glLinkProgram(ID);

    int sucess;
    char infoLog[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &sucess);

    if (!sucess) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void Program::errors() {
    glGetProgramiv(ID, GL_LINK_STATUS, &sucess);

    if (!sucess) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void Program::use() { glUseProgram(ID); }

void Program::resetModelMatrix() { model = glm::mat4(1.0f); }

void Program::setModelMatrix() { setUniform4fv("model", model); }

Program &Program::scale(glm::vec3 scaleProps) {
    model = glm::scale(model, scaleProps);
    return *this;
};

Program &Program::rotate(float degree, glm::vec3 rotateProps) {
    model = glm::rotate(model, glm::radians(degree), rotateProps);
    return *this;
};

Program &Program::translate(glm::vec3 translateProps) {
    model = glm::translate(model, translateProps);
    return *this;
}

void Program::setCamera(core::Camera &camera) {
    setUniform4fv("view", camera.getView());
    setUniform3fv("viewPos", camera.getViewPosition());
    setUniform4fv("projection", camera.getPerspective());
}

void Program::setLight(Light &light) {
    setUniform3fv("light.position", light.position);
    setUniform3fv("light.ambient", light.ambient);
    setUniform3fv("light.diffuse", light.diffuse);
    setUniform3fv("light.specular", light.specular);
}

void Program::setTextures() {
    // Texture
    setUniform1i("material.diffuse", 0);
    setUniform1i("material.specular", 1);
    setUniform1i("material.emission", 2);
    setUniform1f("material.shininess", 1.0f);
}

void Program::setUniform1I(const char name[], GLint value) const { glUniform1i(glGetUniformLocation(ID, name), value); }

void Program::setUniform1f(const char name[], GLfloat value) const { glUniform1f(glGetUniformLocation(ID, name), value); }

void Program::setUniform3fv(const char name[], glm::vec3 &vec) {
    glUniform3fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(vec));
}

void Program::setUniform4fv(const char name[], glm::mat4 &mat) {
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Program::setUniform1i(const char name[], GLint value) { glUniform1i(glGetUniformLocation(ID, name), value); }
} // namespace oriongl::graphics
