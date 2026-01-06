#include "ResourceManager.h"

#include <concepts>
#include <sstream>
#include <unordered_map>
#include <vector>

namespace oriongl::core {
template <typename key, typename value> using cache_map = std::unordered_map<key, std::weak_ptr<value>>;

template <typename Key, typename Value> std::shared_ptr<Value> tryToLockSmartPointer(Key &key, cache_map<Key, Value> &map) {
    auto it = map.find(key);
    if (it == map.end())
        return nullptr;

    return map[key].lock();
}

template <typename Key, typename Value, typename... Args>
std::shared_ptr<Value> instanciateAndCache(Key &key, cache_map<Key, Value> &map, Args &&...args) {
    std::shared_ptr<Value> _ptr = std::make_shared<Value>(std::forward<Args>(args)...);
    map[key] = _ptr;
    return _ptr;
}

template <typename T>
concept streameable = requires(std::ostream &os, T val) {
    { os << val } -> std::same_as<std::ostream &>;
};

template <streameable... Args> std::string concatenateHashKeys(Args &&...args) {
    std::stringstream ss;
    (ss << ... << args);
    return ss.str();
};

Camera &getCamera() {
    static Camera cam{};
    return cam;
};

std::shared_ptr<graphics::Mesh> getCubeData() {
    // clang-format off
    static graphics::vertex_array vertexesCube = {
        // ===== Front (+Z)
        -6.0f, -5.0f,  5.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
         4.0f, -5.0f,  5.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
         4.0f,  5.0f,  5.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
        -6.0f,  5.0f,  5.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,

        // ===== Back (-Z)
         4.0f, -5.0f, -5.0f,   0.0f, 0.0f,-1.0f,   0.0f, 0.0f,
        -6.0f, -5.0f, -5.0f,   0.0f, 0.0f,-1.0f,   1.0f, 0.0f,
        -6.0f,  5.0f, -5.0f,   0.0f, 0.0f,-1.0f,   1.0f, 1.0f,
         4.0f,  5.0f, -5.0f,   0.0f, 0.0f,-1.0f,   0.0f, 1.0f,

        // ===== Left (-X)
        -6.0f, -5.0f, -5.0f,  -1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        -6.0f, -5.0f,  5.0f,  -1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
        -6.0f,  5.0f,  5.0f,  -1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
        -6.0f,  5.0f, -5.0f,  -1.0f, 0.0f, 0.0f,   0.0f, 1.0f,

        // ===== Right (+X)
         4.0f, -5.0f,  5.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
         4.0f, -5.0f, -5.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
         4.0f,  5.0f, -5.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
         4.0f,  5.0f,  5.0f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,

        // ===== Top (+Y)
        -6.0f,  5.0f,  5.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
         4.0f,  5.0f,  5.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
         4.0f,  5.0f, -5.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
        -6.0f,  5.0f, -5.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,

        // ===== Bottom (-Y)
        -6.0f, -5.0f, -5.0f,   0.0f,-1.0f, 0.0f,   0.0f, 0.0f,
         4.0f, -5.0f, -5.0f,   0.0f,-1.0f, 0.0f,   1.0f, 0.0f,
         4.0f, -5.0f,  5.0f,   0.0f,-1.0f, 0.0f,   1.0f, 1.0f,
        -6.0f, -5.0f,  5.0f,   0.0f,-1.0f, 0.0f,   0.0f, 1.0f
    };

    static graphics::indexes_array indexesCube = {
        0,  1,  2,  0,  2,  3,  // Front
        4,  5,  6,  4,  6,  7,  // Back
        8,  9,  10, 8,  10, 11, // Left
        12, 13, 14, 12, 14, 15, // Right
        16, 17, 18, 16, 18, 19, // Top
        20, 21, 22, 20, 22, 23  // Bottom
    };
    // clang-format on

    static auto ptr = std::make_shared<graphics::Mesh>(vertexesCube, indexesCube);
    return ptr;
}

std::shared_ptr<graphics::Mesh> getSphereData(float radius) {
    static cache_map<float, graphics::Mesh> radiusMap;
    auto ptr = tryToLockSmartPointer<float, graphics::Mesh>(radius, radiusMap);
    if (ptr)
        return ptr;

    auto data = generateSphereRadiusVector(radius);
    return instanciateAndCache(radius, radiusMap, data.first, data.second);
}

constexpr std::pair<graphics::vertex_array, graphics::indexes_array> generateSphereRadiusVector(const float radius) {
    std::vector<float> vertexesSphere;
    std::vector<unsigned int> indexesSphere;

    int stacks = 40;   // latitude
    int slices = 1600; // longitude

    for (int i = 0; i <= stacks; ++i) {
        float phi = (static_cast<float>(i) / stacks) * M_PI;
        float y = cosf(phi) * radius;
        float r = sinf(phi) * radius;

        for (int j = 0; j <= slices; ++j) {
            float theta = (static_cast<float>(j) / slices) * 2.0f * M_PI;
            float x = r * cosf(theta);
            float z = r * sinf(theta);

            // posicao
            vertexesSphere.push_back(x);
            vertexesSphere.push_back(y);
            vertexesSphere.push_back(z);

            // normal (apontando para fora)
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

    auto ptr = tryToLockSmartPointer<std::string, graphics::Texture>(tex, texMap);

    if (ptr)
        return ptr;

    return instanciateAndCache(tex, texMap, tex);
}

std::shared_ptr<graphics::Program> getProgram(std::string vertex_src_path, std::string frag_src_path, std::vector<std::string> defines) {
    static cache_map<std::string, graphics::Program> progMap;

    std::string key = concatenateHashKeys(vertex_src_path, frag_src_path, defines.data());

    graphics::Shader vertex_shader{graphics::ShaderType::VERTEX, vertex_src_path, defines};

    graphics::Shader fragment_shader{graphics::ShaderType::FRAGMENT, frag_src_path, defines};

    auto ptr = tryToLockSmartPointer<std::string, graphics::Program>(key, progMap);
    if (ptr)
        return ptr;

    return instanciateAndCache(key, progMap, std::move(vertex_shader), std::move(fragment_shader));
}

std::shared_ptr<graphics::Program> getProgram(const char *vertex_src_path, const char *frag_src_path, std::vector<std::string> defines) {
    static cache_map<std::string, graphics::Program> progMap;
    std::string key = concatenateHashKeys(vertex_src_path, frag_src_path, defines.data());

    graphics::Shader vertex_shader{graphics::ShaderType::VERTEX, vertex_src_path, defines};

    graphics::Shader fragment_shader{graphics::ShaderType::FRAGMENT, frag_src_path, defines};

    auto ptr = tryToLockSmartPointer<std::string, graphics::Program>(key, progMap);
    if (ptr)
        return ptr;

    return instanciateAndCache(key, progMap, std::move(vertex_shader), std::move(fragment_shader));
}

std::shared_ptr<graphics::Material> getMaterial(graphics::MaterialData &mat) {
    static cache_map<std::string, graphics::Material> matMap;
    std::string key = concatenateHashKeys(mat.diffusePath.c_str(), mat.specularPath.c_str(), mat.emissivePath.c_str());
    auto ptr = tryToLockSmartPointer<std::string, graphics::Material>(key, matMap);
    if (ptr)
        return ptr;

    return instanciateAndCache(key, matMap, mat);
}
} // namespace oriongl::core
