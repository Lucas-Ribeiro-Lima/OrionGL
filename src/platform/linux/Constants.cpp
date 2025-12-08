//
// Created by lucas.lima on 07/12/2025.
//

#include <Constants.h>
#include <filesystem>

namespace oriongl::utils::constants {
    std::string getRootPath() {
        static auto path = std::filesystem::canonical("/proc/self/exec");
        return path.string();
    };

    std::string getAssetsPath() {
        static auto assetPath = getRootPath() + "assets";
        return assetPath;
    }

    std::string getShadersPath() {
        static auto shadersPath = getRootPath() + "shaders";
        return shadersPath;
    }
};
