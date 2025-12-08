#pragma once
#include "Model.h"

namespace oriongl::core {
    typedef std::array<float, 3> Point;

    struct CorpData {
        std::vector<std::string> defines;
        graphics::MaterialData mat;
        float radius;
        float rotationScaler;
        float translationScaler;
        Point pos;
    };

    struct ShadersSrc {
        std::string vertex;
        std::string fragment;
    };

    class Corp : public graphics::Model {
        float rotationScaler;
        float translationScaler;

    public:
        Corp(CorpData &data);

        Corp(CorpData &data, ShadersSrc shaders_src);

        void draw() override;
    };
}
