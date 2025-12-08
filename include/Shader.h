#pragma once

#include <string>
#include <vector>
#include <glad.h>

namespace oriongl::graphics {
    enum ShaderType {
        VERTEX = GL_VERTEX_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER,
    };

    class Shader {
    protected:
        char infoLog[512];
        std::string shaderSource;
        std::vector<std::string> defines;
        unsigned int ID;
        int sucess;

    public:
        Shader(ShaderType type, std::string src_path, const std::vector<std::string> &defines);
        ~Shader();
        std::string injectDefines() const;
        unsigned int getId();
        void errors();
    };
}
