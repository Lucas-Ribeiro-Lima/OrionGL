//
// Created by lucas.lima on 30/11/2025.
//

#include <System.h>
#include <Corp.h>
#include <Config.h>

#include "ResourceManager.h"

std::vector<CorpData> planets_data{
        {{ASSETS_DIR "mercury.jpg"}, 2.0f, 5.0f, 0.8f}, // Mercury
        {{ASSETS_DIR "venus.jpg"}, 3.0f, 3.0f, 0.5f}, // Venus
        {
            {
                ASSETS_DIR "earth.jpg",
                ASSETS_DIR "earth_specular_map.tif",
                ASSETS_DIR "earth_nightmap.jpg"
            },
            3.3f, 8.0f, 0.2f
        }, // Earth
        {{ASSETS_DIR "mars.jpg"}, 2.5f, 7.0f, 0.1f}, // Mars
        {{ASSETS_DIR "jupiter.jpg"}, 12.0f, 12.0f, 0.3f}, // Jupiter
        {{ASSETS_DIR "saturn.jpg"}, 10.0f, 10.0f, 0.4f}, // Saturn
        {{ASSETS_DIR "uranus.jpg"}, 4.5f, 6.0f, 0.8f}, // Uranus
        {{ASSETS_DIR "neptune.jpg"}, 4.0f, 5.0f, 0.1f}, // Neptune
    };
std::vector<glm::vec3> planets_positions{
        {-30.0f, 0.0f, -30.0f}, {45.0f, 0.0f, 45.0f}, {-60.0f, 0.0f, -60.0f}, {75.0f, 0.0f, 75.0f},
        {-110.0f, 0.0f, -110.0f}, {150.0f, 0.0f, 150.0f}, {-190.0f, 0.0f, -190.0f}, {230.0f, 0.0f, 230.0f}
};

std::vector<CorpData> stars_data{{{ASSETS_DIR "sun.jpg"}, 20.0f, 0.1f, 0.0f}};
std::vector<glm::vec3> stars_positions{{0.0f, 0.0f, 0.0f}};

PlanetSystem::PlanetSystem(): cam1(getCamera()) {
    for (int i = 0; i < planets_data.size(); i++) {
        std::unique_ptr<Model> planet_ptr = std::make_unique<Corp>(planets_data[i]);
        planets.emplace_back(std::move(planet_ptr), planets_positions[i]);
    }

    for (int i = 0; i < stars_data.size(); i++) {
        std::unique_ptr<Model> sun_ptr = std::make_unique<Corp>(stars_data[i], ShadersSrc{ Constants::VSHADER_1, Constants::FRAG_LIGHT });
        stars.emplace_back(std::move(sun_ptr), stars_positions[i]);
    }
}

void PlanetSystem::process() {
    for (auto& star : stars) {
        star.drawInstances();
    }

    for (auto& planet : planets) {
        planet.drawInstances();
    }
}

Camera &PlanetSystem::getMainCam() {
    return cam1;
}
