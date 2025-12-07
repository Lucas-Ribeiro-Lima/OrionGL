#include "FragmentShader.h"
#include <glad.h>

namespace oriongl::core {
    FragmentShader::FragmentShader(const char *source) : Shader() {
        ID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(ID, 1, &source, 0);
        glCompileShader(ID);

        Shader::errors();
    }
}
