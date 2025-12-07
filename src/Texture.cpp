#include "Texture.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad.h>


#define GL_STB_NULL_PLACEHOLDER 0
//Map for the colors system of images of stb_images

namespace oriongl::core {
    constexpr int colorSystem[4] = {GL_STB_NULL_PLACEHOLDER, GL_STB_NULL_PLACEHOLDER, GL_RGB, GL_RGBA};

    Texture::Texture(const char *path) {
        int width, heigth, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(path, &width, &heigth, &nrChannels, 0);

        glGenTextures(1, &TEX);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TEX);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, colorSystem[nrChannels - 1], width, heigth, 0, colorSystem[nrChannels - 1],
                         GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            glDeleteTextures(1, &TEX);
        }

        stbi_image_free(data);
    }

    GLuint Texture::getTex() const {
        return TEX;
    }
}
