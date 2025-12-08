#pragma once
#include <string>

namespace oriongl::graphics {
    class Texture {
        unsigned int TEX = 0;

    public:
        Texture(std::string texture);

        Texture(std::string texture, bool flip);

        unsigned int getTex() const;
    };
}
