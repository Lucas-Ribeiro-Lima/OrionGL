#include "Corp.h"
#include "GLFW/glfw3.h"
#include "ResourceManager.h"
#include "Constants.h"

namespace oriongl::core {
    Corp::Corp(
        CorpData &data
    ) : Model(
            getSphereData(data.radius),
            getProgram(utils::constants::VSHADER_1, utils::constants::FRAG_1),
            getMaterial(data.mat)
        ), rotationScaler(data.rotationScaler), translationScaler(data.translationScaler) {
    }

    Corp::Corp(
        CorpData &data,
        ShadersSrc shaders_src
    ) : Model(
            getSphereData(data.radius),
            getProgram(shaders_src.vertex, shaders_src.fragment),
            getMaterial(data.mat)
        ), rotationScaler(data.rotationScaler), translationScaler(data.translationScaler) {
    }

    void Corp::draw() {
        float time = glfwGetTime();

        glm::vec3 orbit{
            cos(time * translationScaler),
            0.0f,
            sin(time * translationScaler)
        };

        translateAxis *= orbit;
        rotateAxis += glm::vec3(0, 1, 0);
        rotateDeg = glm::mod(time * rotationScaler, 360.0f);

        Model::draw();
    }
}
