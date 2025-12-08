#pragma once
#include <string>
#include <filesystem>
#include <Config.h>

namespace oriongl::utils::constants {
    // Runtime functions
    std::string getRootPath();

    std::string getAssetsPath();

    std::string getShadersPath();

#if ORIONGL_DEV_MODE
    // Build-time paths (IDE, debug builds)
    inline std::string CORPS_DATA = ASSETS_DIR "solar_system.json";
    inline std::string VSHADER_1 = SHADER_DIR "shader-1.glsl";
    inline std::string FRAG_1 = SHADER_DIR "frag-1.glsl";
    inline std::string FRAG_LIGHT = SHADER_DIR "frag-light.glsl";
    inline std::string TEXTURE_BLACK_FALLBACK = ASSETS_DIR "black_pixel.png";
    inline std::string TEXTURE_WHITE_FALLBACK = ASSETS_DIR "white_pixel.png";
#else
    // Release → resolve at runtime
    inline std::string CORPS_DATA = getAssetsPath() + "solar_system.json";
    inline std::string VSHADER_1 = getShadersPath() + "shader-1.glsl";
    inline std::string FRAG_1 = getShadersPath() + "frag-1.glsl";
    inline std::string FRAG_LIGHT = getShadersPath() + "frag-light.glsl";
    inline std::string TEXTURE_BLACK_FALLBACK = getAssetsPath() + "black_pixel.png";
    inline std::string TEXTURE_WHITE_FALLBACK = getAssetsPath() + "white_pixel.png";
#endif
}
