//
// Created by lucas.lima on 30/11/2025.
//

#include "JsonParser.h"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

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
    c.pos = j.at("position").get<std::array<float, 3> >();
}

JsonParser::system_data JsonParser::readSystemData() {
    planets_data planets;
    stars_data stars;

    std::ifstream input_file{Constants::CORPS_DATA, std::ios::in};
    json parsed_json = json::parse(input_file);

    for (auto &planet_json: parsed_json.at("planets")) {
        CorpData _planet_data = planet_json.get<CorpData>();
        planets.push_back(_planet_data);
    }

    for (auto &star_json: parsed_json.at("stars")) {
        CorpData _star_data = star_json.get<CorpData>();
        stars.push_back(_star_data);
    }

    return std::make_pair(std::move(planets), std::move(stars));
};


