//
// Created by lucas.lima on 30/11/2025.
//

#ifndef OPENGL_LEARNING_SYSTEM_H
#define OPENGL_LEARNING_SYSTEM_H

#include <Instances.h>
#include <vector>

class System {
public:
    virtual void process() = 0;

    virtual ~System() = default;

    virtual Camera &getMainCam() = 0;
};

class PlanetSystem : public System {
private:
    std::vector<Instances> stars;
    std::vector<glm::vec3> stars_position;
    std::vector<Instances> planets;
    std::vector<glm::vec3> planets_position;
    Camera &cam1;

    void initSystem();

public:
    PlanetSystem();

    void process() override;

    ~PlanetSystem() override = default;

    Camera &getMainCam() override;
};

#endif //OPENGL_LEARNING_SYSTEM_H
