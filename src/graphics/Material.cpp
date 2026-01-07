//
// Created by lucas.lima on 12/09/2025.
//

#include "ResourceManager.h"
#include <Material.h>
#include <glad.h>

namespace oriongl::graphics {
#define MAX_TEXTURES 8

Material::Material() {};

void Material::loadTexture(std::string &path) { 
  assert(textures.size() < MAX_TEXTURES && "Exceeded maximum number of textures per material");
  textures.push_back(oriongl::core::getTextureData(path)); 
}

void Material::bindMaterial() {
    size_t number = 0;
    for (auto &texture : textures) {
        glActiveTexture(GL_TEXTURE0 + number++);
        glBindTexture(GL_TEXTURE_2D, texture->getTex());
    }
}
} // namespace oriongl::graphics
