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
        const char *shaderSource;
        unsigned int ID;
        int sucess;

    public:
        Shader(ShaderType type, std::string src_path, std::vector<std::string> defines);
        ~Shader();
        unsigned int getId();

        void errors();
    };
}
