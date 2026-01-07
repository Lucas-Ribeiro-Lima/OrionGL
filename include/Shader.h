#pragma once

#include <glad.h>
#include <string>
#include <vector>

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
    char infoLog[512]{};
    std::string shaderSource;
    std::vector<std::string> defines;
    ShaderType shaderType;
    unsigned int ID;
    int success = 0;

  public:
    Shader(ShaderType type, std::string src_raw, const std::vector<std::string> &defines);
    ~Shader();
    void injectDefines();
    void compileShader() const;
    [[nodiscard]] unsigned int getId() const;
    void errors();
};
} // namespace oriongl::graphics
