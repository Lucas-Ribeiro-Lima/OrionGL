#include "ResourceManager.h"

#include <vector>
#include <unordered_map>
#include <sstream>

template<typename key, typename value>
using cache_map = std::unordered_map<key, std::weak_ptr<value> >;

template<typename Key, typename Value, typename... Args>
std::shared_ptr<Value> tryToLockSmartPointer(Key &key, cache_map<Key, Value> &map, Args &&... args) {
    if (std::shared_ptr<Value> cached_ptr = map[key].lock()) return cached_ptr;

    std::shared_ptr<Value> _ptr = std::make_shared<Value>(std::forward<Args>(args)...);
    map[key] = _ptr;
    return _ptr;
}

constexpr std::pair<std::vector<float>, std::vector<unsigned int> > generateSphereRadiusVector(float radius);

Camera &getCamera() {
    static Camera cam;
    return cam;
};

Mesh &getCubeData() {
    std::vector<float> vertexesCube = {

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //0
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, //1
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, //2
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, //3


        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //4
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, //5
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, //6
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f //7

    };

    std::vector<unsigned int> indexesCube = {
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
    static Mesh ptr{vertexesCube, indexesCube};
    return ptr;
}

std::shared_ptr<Mesh> getSphereData(float radius) {
    static cache_map<float, Mesh> radiusMap;

    if (radiusMap.contains(radius)) {
        if (std::shared_ptr<Mesh> cashed_ptr = radiusMap[radius].lock()) return cashed_ptr;
    }

    std::pair data = generateSphereRadiusVector(radius);
    std::shared_ptr<Mesh> ptr = std::make_shared<Mesh>(data.first, data.second);
    radiusMap.insert({radius, ptr});

    return ptr;
}

constexpr std::pair<std::vector<float>, std::vector<unsigned int> > generateSphereRadiusVector(const float radius) {
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

std::shared_ptr<Texture> getTextureData(const char *tex) {
    static cache_map<const char *, Texture> texMap;

    return tryToLockSmartPointer<const char *, Texture>(tex, texMap, tex);
}

std::shared_ptr<Program> getProgram(const char *vertex, const char *frag) {
    static cache_map<std::string, Program> progMap;

    std::stringstream ss;
    ss << vertex << "," << frag;

    std::string key = ss.str();

    return tryToLockSmartPointer<std::string, Program>(key, progMap, vertex, frag);
}


std::shared_ptr<Material> getMaterial(MaterialData &mat) {
    static cache_map<std::string, Material> matMap;
    std::stringstream ss;

    ss <<
            mat.diffusePath <<
            mat.specularPath <<
            mat.emissivePath << ";";

    std::string key = ss.str();
    return tryToLockSmartPointer<std::string, Material>(key, matMap, mat);
}
