#include <ResourceManagers.h>

#include <memory>
#include <sstream>

namespace {
template <typename Key, typename Value> using cache_map = std::unordered_map<Key, std::weak_ptr<Value>>;

cache_map<std::string, oriongl::graphics::Program> shaderMap;
cache_map<std::string, oriongl::graphics::Mesh> meshMap;
cache_map<std::string, oriongl::graphics::Texture> textureMap;
cache_map<unsigned int, oriongl::graphics::Model> modelMap;

} // namespace

namespace oriongl::core::storage {

template <typename Key, typename Value> std::shared_ptr<Value> tryToLockSmartPointer(Key &key, cache_map<Key, Value> &map) {
    auto it = map.find(key);
    if (it == map.end())
        return nullptr;

    return map[key].lock();
}

template <typename Key, typename Value, typename... Args>
std::shared_ptr<Value> instanciateAndCache(Key &key, cache_map<Key, Value> &map, Args &&...args) {
    auto _ptr = std::make_shared<Value>(std::forward<Args>(args)...);
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

std::shared_ptr<graphics::Program> ShaderManager::getProgram(std::string vertex_src, std::string frag_src,
                                                             std::vector<std::string> defines) {
    std::string key = concatenateHashKeys(vertex_src, frag_src, defines.data());

    auto ptr = tryToLockSmartPointer<std::string, graphics::Program>(key, shaderMap);
    if (ptr)
        return ptr;

    graphics::Shader vertex_shader{graphics::ShaderType::VERTEX, vertex_src, defines};
    graphics::Shader fragment_shader{graphics::ShaderType::FRAGMENT, frag_src, defines};

    return instanciateAndCache(key, shaderMap, std::move(vertex_shader), std::move(fragment_shader));
};

std::shared_ptr<graphics::Mesh> MeshManager::getMesh(std::string mesh_path) {
    // TO DO
    return nullptr;
};

std::shared_ptr<graphics::Texture> TextureManager::getTexture(std::string tex_path) {
    auto ptr = tryToLockSmartPointer<std::string, graphics::Texture>(tex_path, textureMap);

    if (ptr)
        return ptr;

    return instanciateAndCache(tex_path, textureMap, tex_path);
};

graphics::Material loadMaterialHelper(std::vector<std::string> &textures) {
    graphics::Material material;
    for (auto &texture : textures) {
        material.loadTexture(TextureManager::getTexture(texture));
    }
    return material;
};

std::shared_ptr<graphics::Model> ModelManager::getModel(std::shared_ptr<graphics::Program> shader, std::shared_ptr<graphics::Mesh> mesh,
                                     std::vector<std::string> textures) {

    auto material = loadMaterialHelper(textures);
    auto model = std::make_shared<oriongl::graphics::Model>(shader);
    model->loadData(mesh, std::make_shared<graphics::Material>(material));

    return model;
};


std::shared_ptr<graphics::Mesh> MeshLoaderHelper::getCubeMesh(float side_size) {
    // clang-format off
    static graphics::vertex_array vertexesCube = {
        // ===== Front (+Z)
        -side_size, -side_size,  side_size,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
         side_size, -side_size,  side_size,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
         side_size,  side_size,  side_size,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
        -side_size,  side_size,  side_size,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,

        // ===== Back (-Z)
         side_size, -side_size, -side_size,   0.0f, 0.0f,-1.0f,   0.0f, 0.0f,
        -side_size, -side_size, -side_size,   0.0f, 0.0f,-1.0f,   1.0f, 0.0f,
        -side_size,  side_size, -side_size,   0.0f, 0.0f,-1.0f,   1.0f, 1.0f,
         side_size,  side_size, -side_size,   0.0f, 0.0f,-1.0f,   0.0f, 1.0f,

        // ===== Left (-X)
        -side_size, -side_size, -side_size,  -1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        -side_size, -side_size,  side_size,  -1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
        -side_size,  side_size,  side_size,  -1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
        -side_size,  side_size, -side_size,  -1.0f, 0.0f, 0.0f,   0.0f, 1.0f,

        // ===== Right (+X)
         side_size, -side_size,  side_size,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
         side_size, -side_size, -side_size,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
         side_size,  side_size, -side_size,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
         side_size,  side_size,  side_size,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,

        // ===== Top (+Y)
        -side_size,  side_size,  side_size,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
         side_size,  side_size,  side_size,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
         side_size,  side_size, -side_size,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
        -side_size,  side_size, -side_size,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,

        // ===== Bottom (-Y)
        -side_size, -side_size, -side_size,   0.0f,-1.0f, 0.0f,   0.0f, 0.0f,
         side_size, -side_size, -side_size,   0.0f,-1.0f, 0.0f,   1.0f, 0.0f,
         side_size, -side_size,  side_size,   0.0f,-1.0f, 0.0f,   1.0f, 1.0f,
        -side_size, -side_size,  side_size,   0.0f,-1.0f, 0.0f,   0.0f, 1.0f
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

std::shared_ptr<graphics::Mesh> MeshLoaderHelper::getSphereMesh(float radius) {
    static cache_map<float, graphics::Mesh> radiusMap;
    auto ptr = tryToLockSmartPointer<float, graphics::Mesh>(radius, radiusMap);
    if (ptr)
        return ptr;

    auto data = generateSphereRadiusVector(radius);
    return instanciateAndCache(radius, radiusMap, data.first, data.second);
}
} // namespace oriongl::core::storage
