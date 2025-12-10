#pragma once

#include <string>
#include <vector>
#include <glad.h>

namespace oriongl::graphics {
    enum ShaderType {
        VERTEX = GL_VERTEX_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER,
    };

    struct ShadersSrc {
        std::string vertex;
        std::string fragment;
    };

    class Shader {
    protected:
        char infoLog[512] = {};
        std::string shaderSource;
        std::vector<std::string> defines;
        unsigned int ID;
        int success = 0;

    public:
        Shader(ShaderType type, const std::string& src_path, const std::vector<std::string> &defines);
        Shader(ShaderType type, const char* src_raw, const std::vector<std::string> &defines);
        ~Shader();
        void injectDefines();
        void compileShader() const;
        [[nodiscard]] unsigned int getId() const;
        void errors();
    };
}
