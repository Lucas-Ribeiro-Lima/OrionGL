#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "Material.h"
#include "Program.h"
#include "Mesh.h"


namespace oriongl::graphics {
    using uint = unsigned int;

    class Model {
    protected:
        glm::vec3 translateAxis = glm::vec3(0.0f);
        glm::vec3 scaleAxis = glm::vec3(1.0f);
        glm::vec3 rotateAxis = glm::vec3(1.0f);

        std::shared_ptr<Mesh> mesh = nullptr;
        std::shared_ptr<Program> program = nullptr;
        std::shared_ptr<Material> material = nullptr;

        uint VAO = 0;
        float rotateDeg = 0;

        bool wireframe = false;

        void saveBuffer();

        void genVertexArrayBuffer();

        void bindGeometry() const;

        void bindTexture() const;

    public:
        Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Program> program);

        Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Program> program,
              std::shared_ptr<Material> material);

        virtual ~Model() = default;

        uint getID() const;

        Model &setProgram(std::shared_ptr<Program> prg);

        Model &setTranslate(glm::vec3 axis);

        Model &setRotate(float deg, glm::vec3 axis);

        Model &setScale(glm::vec3 axis);

        void setWireframe(bool state);

        virtual void draw();
    };
}
