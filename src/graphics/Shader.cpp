#include "Shader.h"
#include "Utils.h"
#include <glad.h>
#include <format>
#include <sstream>

namespace oriongl::graphics {
    Shader::Shader(ShaderType type, std::string src_path, const std::vector<std::string> &defines):
        ID(glCreateShader(type)),
        shaderSource(src_path),
        defines(defines)
    {
        std::string src_processed = injectDefines();
        const char* raw_data = src_processed.c_str();
        glShaderSource(ID, 1, &raw_data, 0);
        glCompileShader(ID);

        errors();
    }

    std::string Shader::injectDefines() const {
        std::stringstream ss;
        std::string source_data = utils::readFile(shaderSource);

        const size_t first_break_line = source_data.find_first_of("\n");
        ss << source_data.substr(0, first_break_line);
        for (auto& define : defines) {
            ss << "\n#define " << define;
        }
        ss << "\n";
        ss << source_data.substr(first_break_line);

        return ss.str();
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
