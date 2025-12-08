#include "Shader.h"
#include "Utils.h"
#include <glad.h>
#include <format>

namespace oriongl::graphics {
    void Shader::errors() {
        glGetShaderiv(ID, GL_COMPILE_STATUS, &sucess);

        if (!sucess) {
            glGetShaderInfoLog(ID, 512, NULL, infoLog);
            utils::logger(std::format("ORIONGL::CORE::SHADER::COMPILATION_FAILED + {}", infoLog).c_str());
        }
    }

    GLuint Shader::getId() {
        return ID;
    }
}
