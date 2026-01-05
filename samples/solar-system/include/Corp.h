#pragma once
#include "Model.h"

namespace oriongl::samples::solar_system {
    typedef std::array<float, 3> Point;

    struct CorpData {
        std::vector<std::string> defines;
        graphics::MaterialData mat;
        float radius;
        float rotationScaler;
        float translationScaler;
        Point pos;
    };

    class Corp : public graphics::Model {
        float rotationScaler;
        float translationScaler;

    public:
        Corp(CorpData &data);

        Corp(CorpData &data, graphics::ShadersSrc shaders_src);

        void draw() override;
    };
}
