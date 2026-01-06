//
// Created by lucas.lima on 30/11/2025.
//

#include <Constants.h>
#include <Corp.h>
#include <JsonParser.h>
#include <PlanetRenderer.h>
#include <ResourceManager.h>

namespace oriongl::samples::solar_system {
PlanetRenderer::PlanetRenderer() : cam1(core::getCamera()) { loadData(); }

void PlanetRenderer::render() {
    for (auto &star : stars) {
        star.drawInstances();
    }

    for (auto &planet : planets) {
        planet.drawInstances();
    }
}

core::Camera &PlanetRenderer::getMainCam() { return cam1; }

void PlanetRenderer::loadData() {
    auto system_data = utils::JsonParser::readSystemData();

    std::vector<CorpData> planets_list = system_data.first;
    std::vector<CorpData> stars_list = system_data.second;

    for (auto &_planet : planets_list) {
        std::unique_ptr<graphics::Model> planet_ptr = std::make_unique<Corp>(_planet);
        planets.emplace_back(std::move(planet_ptr));
        planets.back().addInstance(graphics::ModelData{{_planet.pos[0], _planet.pos[1], _planet.pos[2]}});
    }

    for (auto &_star : stars_list) {
        std::unique_ptr<graphics::Model> star_ptr = std::make_unique<Corp>(_star, graphics::ShadersSrc{
                                                                                      utils::constants::VSHADER_1,
                                                                                      utils::constants::FRAG_LIGHT,
                                                                                  });

        planets.emplace_back(std::move(star_ptr));
        planets.back().addInstance(graphics::ModelData{glm::vec3(0.0f)});
    }
};
} // namespace oriongl::samples::solar_system
