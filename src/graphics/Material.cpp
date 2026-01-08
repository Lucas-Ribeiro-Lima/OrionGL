//
// Created by lucas.lima on 12/09/2025.
//

#include <Material.h>
#include <cassert>
#include <glad.h>

namespace oriongl::graphics {
#define MAX_TEXTURES 8

Material::Material() {};

void Material::loadTexture(std::shared_ptr<oriongl::graphics::Texture> texture) { 
  assert(textures.size() < MAX_TEXTURES && "Exceeded maximum number of textures per material");
  textures.push_back(std::move(texture)); 
}

void Material::bindMaterial() {
    size_t number = 0;
    for (auto &texture : textures) {
        glActiveTexture(GL_TEXTURE0 + number++);
        glBindTexture(GL_TEXTURE_2D, texture->getTex());
    }
}
} // namespace oriongl::graphics
