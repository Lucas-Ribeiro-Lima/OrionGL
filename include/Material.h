//
// Created by lucas.lima on 10/09/2025.
//

#ifndef OPENGL_LEARNING_MATERIAL_H
#define OPENGL_LEARNING_MATERIAL_H

#include "Texture.h"

#include <memory>
#include <vector>
#include <string>

namespace oriongl::graphics {
    class Material {
        std::vector<std::shared_ptr<Texture>> textures;

    public:
        Material();
        void loadTexture(std::shared_ptr<Texture> texture);
        void bindMaterial();
    };
}

#endif //OPENGL_LEARNING_MATERIAL_H
