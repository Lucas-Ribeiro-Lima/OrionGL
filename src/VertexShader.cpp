#include "VertexShader.h"
#include <glad.h>

namespace oriongl::core {
    VertexShader::VertexShader(const char *source) : Shader() {
        ID = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(ID, 1, &source, 0);
        glCompileShader(ID);

        errors();
    }
}
