#include "Shader.h"
#include "Utils.h"
#include <glad.h>
#include <format>

namespace oriongl::graphics {
    Shader::Shader(ShaderType type, std::string src_path, std::vector<std::string> defines) {
        ID = glCreateShader(type);

        auto src = utils::readFile(src_path);
        const char* src_raw = src.c_str();
        glShaderSource(ID, 1, &src_raw, 0);
        glCompileShader(ID);

        errors();
    }

    Shader::~Shader() {
        glDeleteShader(this->ID);
    }

    void Shader::errors() {
        glGetShaderiv(ID, GL_COMPILE_STATUS, &sucess);

        if (!sucess) {
            glGetShaderInfoLog(ID, 512, NULL, infoLog);
            utils::logger(std::format("ORIONGL::CORE::SHADER::COMPILATION_FAILED + {}", infoLog));
        }
    }

    GLuint Shader::getId() {
        return ID;
    }

}
