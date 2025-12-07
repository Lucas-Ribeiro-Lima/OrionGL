#pragma once

namespace oriongl::core {
    class Shader {
    protected:
        char infoLog[512];
        const char *shaderSource;
        unsigned int ID;
        int sucess;

    public:
        unsigned int getId();

        void errors();
    };
}
