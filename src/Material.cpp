//
// Created by lucas.lima on 12/09/2025.
//

#include <Material.h>
#include <glad.h>
#include "Constants.h"
#include "ResourceManager.h"

namespace oriongl::core {
    Material::Material() : diffuse(ecs::getTextureData(utils::constants::TEXTURE_BLACK_FALLBACK)),
                           specular(ecs::getTextureData(utils::constants::TEXTURE_BLACK_FALLBACK)),
                           emissive(ecs::getTextureData(utils::constants::TEXTURE_BLACK_FALLBACK)) {
    }

    Material::Material(MaterialData &mat) : m_data(std::move(mat)) {
        diffuse = ecs::getTextureData(m_data.diffusePath.c_str());
        specular = ecs::getTextureData(m_data.specularPath.c_str());
        emissive = ecs::getTextureData(m_data.emissivePath.c_str());
    };

    void Material::bindMaterial() {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuse->getTex());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specular->getTex());
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, emissive->getTex());
    }
}
