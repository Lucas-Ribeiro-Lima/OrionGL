#pragma once
#include "Shader.h"

namespace oriongl::core {
    class VertexShader :
            public Shader {
    public:
        VertexShader(const char *source);
    };
}
