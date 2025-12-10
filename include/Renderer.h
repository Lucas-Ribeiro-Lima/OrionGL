//
// Created by lucas.lima on 30/11/2025.
//

#ifndef OPENGL_LEARNING_SYSTEM_H
#define OPENGL_LEARNING_SYSTEM_H

#include <Instances.h>
#include <Camera.h>
#include <vector>

namespace oriongl::core {
    class Renderer {
        std::vector<Instances> data;
        Camera &cam1;

    public:
		Renderer();
        virtual ~Renderer() = default;

        virtual void render();
        virtual Camera &getMainCam();
    };
}

#endif //OPENGL_LEARNING_SYSTEM_H
