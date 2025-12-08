#pragma once

namespace oriongl::graphics {
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
