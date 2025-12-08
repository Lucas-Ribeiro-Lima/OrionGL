#include "ResourceManager.h"

#include <vector>
#include <unordered_map>
#include <sstream>
#include <concepts>

namespace oriongl::core {
    template<typename key, typename value>
    using cache_map = std::unordered_map<key, std::weak_ptr<value> >;

    template<typename Key, typename Value, typename... Args>
    std::shared_ptr<Value> tryToLockSmartPointer(Key &key, cache_map<Key, Value> &map, Args &&... args) {
        if (std::shared_ptr<Value> cached_ptr = map[key].lock()) return cached_ptr;

        std::shared_ptr<Value> _ptr = std::make_shared<Value>(std::forward<Args>(args)...);
        map[key] = _ptr;
        return _ptr;
    }

    template<typename T>
    concept streameable = requires(std::ostream &os, T val)
    {
        { os << val } -> std::same_as<std::ostream &>;
    };

    template<streameable... Args>
    std::string concatenateHashKeys(Args &&... args) {
        std::stringstream ss;
        (ss << ... << args);
        return ss.str();
    };

    Camera &getCamera() {
        static Camera cam{};
        return cam;
    };

    graphics::Mesh &getCubeData() {
        graphics::vertex_array vertexesCube = {

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //0
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, //1
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, //2
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, //3


            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //4
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, //5
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, //6
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f //7

        };

        graphics::indexes_array indexesCube = {
            0, 1, 2, //0 Front
            0, 2, 3, //1 Front

            4, 5, 6, //2 Rear
            4, 6, 7, //3 Rear

            4, 0, 3, //4 Face-left
            4, 3, 7, //5 Face-left

            3, 6, 7, //6 Face-up
            2, 3, 6, //7 Face-up

            2, 5, 6, //8 Face-right
            1, 2, 5, //9 Face-right

            0, 4, 5, //10 Bottom
            0, 1, 5, //11 Bottom
        };
        static graphics::Mesh ptr{vertexesCube, indexesCube};
        return ptr;
    }

    std::shared_ptr<graphics::Mesh> getSphereData(float radius) {
        static cache_map<float, graphics::Mesh> radiusMap;

        if (radiusMap.contains(radius)) {
            if (std::shared_ptr<graphics::Mesh> cashed_ptr = radiusMap[radius].lock()) return cashed_ptr;
        }

        std::pair data = generateSphereRadiusVector(radius);
        std::shared_ptr<graphics::Mesh> ptr = std::make_shared<graphics::Mesh>(data.first, data.second);
        radiusMap.insert({radius, ptr});

        return ptr;
    }

    constexpr std::pair<graphics::vertex_array, graphics::indexes_array>
    generateSphereRadiusVector(const float radius) {
        std::vector<float> vertexesSphere;
        std::vector<unsigned int> indexesSphere;

        int stacks = 40; // latitude
        int slices = 1600; // longitude

        for (int i = 0; i <= stacks; ++i) {
            float phi = (static_cast<float>(i) / stacks) * M_PI;
            float y = cosf(phi) * radius;
            float r = sinf(phi) * radius;

            for (int j = 0; j <= slices; ++j) {
                float theta = (static_cast<float>(j) / slices) * 2.0f * M_PI;
                float x = r * cosf(theta);
                float z = r * sinf(theta);

                // posi��o
                vertexesSphere.push_back(x);
                vertexesSphere.push_back(y);
                vertexesSphere.push_back(z);


                // cor (apontando para fora)
                vertexesSphere.push_back(x);
                vertexesSphere.push_back(y);
                vertexesSphere.push_back(z);


                // coordenadas de textura
                vertexesSphere.push_back(1.0f - (static_cast<float>(j) / slices));
                vertexesSphere.push_back(1.0f - (static_cast<float>(i) / stacks));
            }
        }

        // Indices
        for (int i = 0; i < stacks; ++i) {
            for (int j = 0; j < slices; ++j) {
                int first = (i * (slices + 1)) + j;
                int second = first + slices + 1;

                indexesSphere.push_back(first);
                indexesSphere.push_back(second);
                indexesSphere.push_back(first + 1);

                indexesSphere.push_back(second);
                indexesSphere.push_back(second + 1);
                indexesSphere.push_back(first + 1);
            }
        }

        return std::pair{vertexesSphere, indexesSphere};
    }

    std::shared_ptr<graphics::Texture> getTextureData(std::string tex) {
        static cache_map<std::string, graphics::Texture> texMap;

        return tryToLockSmartPointer<std::string, graphics::Texture>(tex, texMap, tex);
    }

    std::shared_ptr<graphics::Program> getProgram(
        std::string vertex_src_path,
        std::string frag_src_path,
        std::vector<std::string> defines) {
        static cache_map<std::string, graphics::Program> progMap;
        std::string key = concatenateHashKeys(vertex_src_path, frag_src_path, defines.data());

        graphics::Shader vertex_shader{
            graphics::ShaderType::VERTEX,
            vertex_src_path,
            defines
        };

        graphics::Shader fragment_shader{
            graphics::ShaderType::FRAGMENT,
            frag_src_path,
            defines
        };

        return tryToLockSmartPointer<std::string, graphics::Program>(
            key,
            progMap,
            std::move(vertex_shader),
            std::move(fragment_shader)
        );
    }


    std::shared_ptr<graphics::Material> getMaterial(graphics::MaterialData &mat) {
        static cache_map<std::string, graphics::Material> matMap;
        std::string key = concatenateHashKeys(
            mat.diffusePath.c_str(),
            mat.specularPath.c_str(),
            mat.emissivePath.c_str());
        return tryToLockSmartPointer<std::string, graphics::Material>(key, matMap, mat);
    }
}
