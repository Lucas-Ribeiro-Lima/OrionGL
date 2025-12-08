//
// Created by lucas.lima on 30/11/2025.
//

#include "JsonParser.h"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

namespace oriongl::core {
    void from_json(const json &j, CorpData &c) {
        c.rotationScaler = j.value("rotation_speed", 1.0f);
        c.translationScaler = j.value("translation_speed", 1.0f);
        c.radius = j.value("radius", 1.0f);

        if (j.contains("defines") && j["defines"].is_array())
            c.defines = j["defines"].get<std::vector<std::string>>();

        if (j.contains("textures") && j["textures"].is_array()) {
            auto &tex = j["textures"];

            if (tex.size() > 0) c.mat.diffusePath = utils::constants::ASSETS_PATH + tex[0].get<std::string>();
            if (tex.size() > 1) c.mat.specularPath = utils::constants::ASSETS_PATH + tex[1].get<std::string>();
            if (tex.size() > 2) c.mat.emissivePath = utils::constants::ASSETS_PATH + tex[2].get<std::string>();
        }

        if (j.at("position").size() != 3) throw std::runtime_error("Corrupted json file");
        c.pos = j.at("position").get<std::array<float, 3> >();
    }
}


namespace oriongl::utils {
    JsonParser::system_data JsonParser::readSystemData() {
        planets_data planets;
        stars_data stars;

        std::ifstream input_file{constants::CORPS_DATA, std::ios::in};
        json parsed_json = json::parse(input_file);

        for (auto &planet_json: parsed_json.at("planets")) {
            planets.push_back(planet_json.get<core::CorpData>());
        }

        for (auto &star_json: parsed_json.at("stars")) {
            stars.push_back(star_json.get<core::CorpData>());
        }

        return std::make_pair(std::move(planets), std::move(stars));
    };
}
