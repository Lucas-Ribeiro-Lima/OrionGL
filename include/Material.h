//
// Created by lucas.lima on 10/09/2025.
//

#ifndef OPENGL_LEARNING_MATERIAL_H
#define OPENGL_LEARNING_MATERIAL_H

#include "Texture.h"
#include "Constants.h"

#include <memory>
#include <string>

namespace oriongl::graphics {
    struct MaterialData {
        std::string diffusePath = utils::constants::TEXTURE_BLACK_FALLBACK;
        std::string specularPath = utils::constants::TEXTURE_BLACK_FALLBACK;
        std::string emissivePath = utils::constants::TEXTURE_BLACK_FALLBACK;
    };

    class Material {
        std::shared_ptr<Texture> diffuse;
        std::shared_ptr<Texture> specular;
        std::shared_ptr<Texture> emissive;
        MaterialData m_data;
        float shininess = 1.0f;

    public:
        Material();

        Material(MaterialData &mat);

        void bindMaterial();
    };
}

#endif //OPENGL_LEARNING_MATERIAL_H
