//
// Created by lucas.lima on 30/11/2025.
//

#include <PlanetRenderer.h>
#include <Corp.h>
#include <Constants.h>
#include <JsonParser.h>
#include <ResourceManager.h>

namespace oriongl::samples {
    PlanetRenderer::PlanetRenderer() : cam1(core::getCamera()) {
        loadData();
    }

    void PlanetRenderer::render() {
        for (auto &star: stars) {
            star.drawInstances();
        }

        for (auto &planet: planets) {
            planet.drawInstances();
        }
    }

    core::Camera &PlanetRenderer::getMainCam() {
        return cam1;
    }

    void PlanetRenderer::loadData() {
        auto system_data = utils::JsonParser::readSystemData();

        std::vector<CorpData> planets_list = system_data.first;
        std::vector<CorpData> stars_list = system_data.second;

        for (auto &_planet: planets_list) {
            std::unique_ptr<graphics::Model> planet_ptr = std::make_unique<Corp>(_planet);

            auto _positions = std::make_shared<glm::vec3>(_planet.pos[0], _planet.pos[1], _planet.pos[2]);
            planets.emplace_back(std::move(planet_ptr));
            planets.back().addInstance(std::move(_positions));
        }

        for (auto &_star: stars_list) {
            std::unique_ptr<graphics::Model> star_ptr = std::make_unique<Corp>(_star, graphics::ShadersSrc{
                                                                         utils::constants::VSHADER_1,
                                                                         utils::constants::FRAG_LIGHT,
                                                                     });

            auto _positions = std::make_shared<glm::vec3>(_star.pos[0], _star.pos[1], _star.pos[2]);
            planets.emplace_back(std::move(star_ptr));
            planets.back().addInstance(std::move(_positions));
        }
    };
}
