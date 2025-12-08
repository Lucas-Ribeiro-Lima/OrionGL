//
// Created by lucas.lima on 30/11/2025.
//

#include <System.h>
#include <Corp.h>
#include <JsonParser.h>
#include <ResourceManager.h>

namespace oriongl::core {
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

    core::Camera &PlanetSystem::getMainCam() {
        return cam1;
    }

    void PlanetSystem::initSystem() {
        auto system_data = utils::JsonParser::readSystemData();

        std::vector<core::CorpData> planets_list = system_data.first;
        std::vector<core::CorpData> stars_list = system_data.second;

        for (auto &_planet: planets_list) {
            std::unique_ptr<graphics::Model> planet_ptr = std::make_unique<core::Corp>(_planet);

            auto _positions = std::make_shared<glm::vec3>(_planet.pos[0], _planet.pos[1], _planet.pos[2]);
            planets.emplace_back(std::move(planet_ptr));
            planets.back().addInstance(std::move(_positions));
        }

        for (auto &_star: stars_list) {
            std::unique_ptr<graphics::Model> star_ptr = std::make_unique<core::Corp>(_star, core::ShadersSrc{
                                                                         utils::constants::VSHADER_1,
                                                                         utils::constants::FRAG_LIGHT,
                                                                     });

            auto _positions = std::make_shared<glm::vec3>(_star.pos[0], _star.pos[1], _star.pos[2]);
            planets.emplace_back(std::move(star_ptr));
            planets.back().addInstance(std::move(_positions));
        }
    };
}
