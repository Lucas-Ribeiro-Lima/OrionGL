#pragma once
#include "Shader.h"

namespace oriongl::core {
    class FragmentShader :
            public Shader {
    public:
        FragmentShader(const char *source);
    };
}
