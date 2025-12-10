#include "Shader.h"
#include "Utils.h"
#include <glad.h>
#include <format>
#include <sstream>

namespace oriongl::graphics {
    Shader::Shader(ShaderType type, const std::string& src_path, const std::vector<std::string> &defines):
        ID(glCreateShader(type)),
        defines(defines)
    {
        shaderSource = utils::readFile(src_path);
        injectDefines();
        compileShader();
        errors();
    }

    Shader::Shader(ShaderType type, const char *src_raw, const std::vector<std::string> &defines):
        ID(glCreateShader(type)),
        shaderSource(src_raw),
        defines(defines)
    {
        injectDefines();
        compileShader();
        errors();
    }

    void Shader::injectDefines() {
        std::stringstream ss;
        const size_t first_break_line = shaderSource.find_first_of("\n");
        ss << shaderSource.substr(0, first_break_line);
        for (auto& define : defines) {
            ss << "\n#define " << define;
        }
        ss << "\n";
        ss << shaderSource.substr(first_break_line);

        shaderSource = ss.str();
    }

    void Shader::compileShader() const {
        const char* raw = &shaderSource[0];
        glShaderSource(ID, 1, &raw, 0);
        glCompileShader(ID);
    }

    Shader::~Shader() {
        glDeleteShader(this->ID);
    }

    void Shader::errors() {
        glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(ID, 512, NULL, infoLog);
            utils::logger(std::format("ORIONGL::CORE::SHADER::COMPILATION_FAILED + {}", infoLog));
        }
    }

    GLuint Shader::getId() const {
        return ID;
    }

}
