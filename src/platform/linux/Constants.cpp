//
// Created by lucas.lima on 07/12/2025.
//

#include <Constants.h>
#include <Config.h>

#include <unistd.h>
#include <vector>
#include <filesystem>
#include <linux/limits.h>

namespace oriongl::utils::constants {
    std::string getRootPath() {
        static auto rootPath = []() -> std::string {
            std::vector<char> buffer(PATH_MAX);
            ssize_t size = readlink("/proc/self/exe", buffer.data(), PATH_MAX - 1);

            if (size == -1) throw std::runtime_error("Could not read root path to get resources");

            buffer[size] = '\0';

            std::filesystem::path dirPath{buffer.data()};

            return dirPath.parent_path().string();
        }();

        return rootPath;
    };

    std::string getAssetsPath() {
        static auto assetPath = []() -> std::string {
            auto path =
                    std::filesystem::path(getRootPath())
                    .parent_path()
                    / "share"
                    / PROJECT_NAME
                    / "assets";

            if (!std::filesystem::exists(path)) {
                throw std::runtime_error("Could not resources folder, restore the installation");
            }

            path = std::filesystem::canonical(path);
            return path.string();
        }();

        return assetPath;
    }

    std::string getShadersPath() {
        static auto shadersPath = []() -> std::string {
            auto path =
                    std::filesystem::path(getRootPath())
                    .parent_path()
                    / "share"
                    / PROJECT_NAME
                    / "shaders";

            if (!std::filesystem::exists(path)) {
                throw std::runtime_error("Could not resources folder, restore the installation");
            }

            path = std::filesystem::canonical(path);
            return path.string();
        }();

        return shadersPath;
    }
};
