#pragma once
#include "Shader.h"

namespace oriongl::graphics {
    class VertexShader :
            public Shader {
    public:
        VertexShader(const char *source);
    };
}
