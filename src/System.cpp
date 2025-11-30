//
// Created by lucas.lima on 30/11/2025.
//

#include <System.h>
#include <Corp.h>
#include <Config.h>
#include <ResourceManager.h>

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
void from_json(const json &j, CorpData &c);

PlanetSystem::PlanetSystem() : cam1(getCamera()) {
    initSystem();
}

void PlanetSystem::process() {
    for (auto &star: stars) {
        star.drawInstances();
    }

    for (auto &planet: planets) {
        planet.drawInstances();
    }
}

Camera &PlanetSystem::getMainCam() {
    return cam1;
}

void PlanetSystem::initSystem() {
    std::ifstream input_file{Constants::CORPS_DATA, std::ios::in};
    json parsed_json = json::parse(input_file);

    for (auto &planet_json: parsed_json.at("planets")) {
        CorpData _planet_data = planet_json.get<CorpData>();
        std::unique_ptr<Model> planet_ptr = std::make_unique<Corp>(_planet_data);

        glm::vec3 _positions{ _planet_data.pos[0], _planet_data.pos[1], _planet_data.pos[2] };
        planets_position.push_back(_positions);
        planets.emplace_back(std::move(planet_ptr), _positions);
    }

    for (auto &star_json: parsed_json.at("stars")) {
        CorpData _star_data = star_json.get<CorpData>();
        std::unique_ptr<Model> star_ptr = std::make_unique<Corp>(_star_data, ShadersSrc{
            Constants::VSHADER_1,
            Constants::FRAG_LIGHT
        });

        glm::vec3 _positions{ _star_data.pos[0], _star_data.pos[1], _star_data.pos[2] };
        stars_position.push_back(_positions);
        stars.emplace_back(std::move(star_ptr), _positions);
    }
};


 void from_json(const json &j, CorpData &c) {
    c.rotationScaler = j.at("rotation_speed");
    c.translationScaler = j.at("translation_speed");
    c.radius = j.at("radius");

    if (j.contains("textures") && j["textures"].is_array()) {
        auto &tex = j["textures"];

        if (tex.size() > 0) c.mat.diffusePath = ASSETS_DIR + tex[0].get<std::string>();
        if (tex.size() > 1) c.mat.specularPath = ASSETS_DIR + tex[1].get<std::string>();
        if (tex.size() > 2) c.mat.emissivePath = ASSETS_DIR + tex[2].get<std::string>();
    }

    if (j.at("position").size() != 3) throw std::runtime_error("Corrupted json file");
    c.pos = j.at("position").get<std::array<float, 3>>();
}