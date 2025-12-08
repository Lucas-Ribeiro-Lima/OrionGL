#pragma once
#include "string"
#include <Config.h>

namespace oriongl::utils::constants {
    std::string getRootPath();

    std::string getAssetsPath();

    std::string getShadersPath();

    inline auto CORPS_DATA = ASSETS_DIR  "solar_system.json";
    inline auto VSHADER_1 = SHADER_DIR  "shader-1.glsl";
    inline auto FRAG_1 = SHADER_DIR  "frag-1.glsl";
    inline auto FRAG_LIGHT = SHADER_DIR  "frag-light.glsl";
    inline auto TEXTURE_BLACK_FALLBACK = ASSETS_DIR  "black_pixel.png";
    inline auto TEXTURE_WHITE_FALLBACK = ASSETS_DIR  "white_pixel.png";
};
