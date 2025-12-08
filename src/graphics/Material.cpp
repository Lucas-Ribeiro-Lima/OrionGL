//
// Created by lucas.lima on 12/09/2025.
//

#include <Material.h>
#include <glad.h>
#include "ResourceManager.h"

namespace oriongl::graphics {
    Material::Material(MaterialData &mat) : m_data(std::move(mat)) {
        diffuse = core::getTextureData(m_data.diffusePath);
        specular = core::getTextureData(m_data.specularPath);
        emissive = core::getTextureData(m_data.emissivePath);
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
