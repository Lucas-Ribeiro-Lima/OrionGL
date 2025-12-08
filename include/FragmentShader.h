#pragma once
#include "Shader.h"

namespace oriongl::graphics {
    class FragmentShader :
            public Shader {
    public:
        FragmentShader(const char *source);
    };
}
