#pragma once
#include <string>
#include <filesystem>

namespace oriongl::samples::utils::constants {
    // Runtime functions
    std::string getRootPath();

    std::string getAssetsPath();

    std::string getShadersPath();

    inline std::string ASSETS_PATH = getAssetsPath();
    inline std::string SHADER_PATH = getShadersPath();

    inline std::string CORPS_DATA = ASSETS_PATH + "solar_system.json";
    inline std::string VSHADER_1 = SHADER_PATH + "shader-1.glsl";
    inline std::string FRAG_1 = SHADER_PATH + "frag-1.glsl";
    inline std::string FRAG_LIGHT = SHADER_PATH + "frag-light.glsl";
    inline std::string TEXTURE_BLACK_FALLBACK = ASSETS_PATH + "black_pixel.png";
    inline std::string TEXTURE_WHITE_FALLBACK = ASSETS_PATH + "white_pixel.png";
}
