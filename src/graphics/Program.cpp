#include "Program.h"
#include "ResourceManager.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "Utils.h"

#include <string>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad.h>

namespace oriongl::graphics {
    Program::Program(const char *vertex, const char *fragment) : cam(core::getCamera()) {
        VertexShader vShader(utils::readFile(vertex).c_str());
        FragmentShader fShader(utils::readFile(fragment).c_str());

        ID = glCreateProgram();
        GLuint shaderId = vShader.getId();
        GLuint fragmentId = fShader.getId();

        glAttachShader(ID, shaderId);
        glAttachShader(ID, fragmentId);
        glLinkProgram(ID);

        int sucess;
        char infoLog[512];
        glGetProgramiv(ID, GL_LINK_STATUS, &sucess);

        if (!sucess) {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        glDeleteShader(shaderId);
        glDeleteShader(fragmentId);
    }

    void Program::errors() {
        glGetProgramiv(ID, GL_LINK_STATUS, &sucess);

        if (!sucess) {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }

    void Program::use() {
        view = cam.getView();
        viewPos = cam.getViewPosition();
        projection = cam.getPerspective();

        glUseProgram(ID);
        setCommonUniforms();
    }

    Program &Program::resetT() {
        model = glm::mat4(1.0f);
        return *this;
    }

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

    void Program::setCommonUniforms() {
        //Transformations
        setUniform4fv("model", model);
        setUniform4fv("view", view);
        setUniform4fv("projection", projection);
        setUniform3fv("viewPos", viewPos);

        //Light position
        setUniform3fv("light.position", light.position);
        setUniform3fv("light.ambient", light.ambient);
        setUniform3fv("light.diffuse", light.diffuse);
        setUniform3fv("light.specular", light.specular);

        //Texture
        setUniform1i("material.diffuse", 0);
        setUniform1i("material.specular", 1);
        setUniform1i("material.emission", 2);
        setUniform1f("material.shininess", 1.0f);
    }

    void Program::setUniform1I(const char name[], GLint value) const {
        glUniform1i(glGetUniformLocation(ID, name), value);
    }

    void Program::setUniform1f(const char name[], GLfloat value) const {
        glUniform1f(glGetUniformLocation(ID, name), value);
    }

    void Program::setUniform3fv(const char name[], glm::vec3 &vec) {
        glUniform3fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(vec));
    }

    void Program::setUniform4fv(const char name[], glm::mat4 &mat) {
        glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void Program::setUniform1i(const char name[], GLint value) {
        glUniform1i(glGetUniformLocation(ID, name), value);
    }
}
