//
// Created by lucas.lima on 30/11/2025.
//

#ifndef OPENGL_LEARNING_JSONPARSER_H
#define OPENGL_LEARNING_JSONPARSER_H

#include "Corp.h"

namespace oriongl::samples::utils {

    class JsonParser {
    public:
        using planets_data = std::vector<CorpData>;
        using stars_data = std::vector<CorpData>;
        using system_data = std::pair<planets_data, stars_data>;

        static system_data readSystemData();
    };
}

#endif //OPENGL_LEARNING_JSONPARSER_H