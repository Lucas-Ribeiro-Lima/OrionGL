#include "Model.h"
#include <glad.h>

namespace oriongl::core {
    Model::Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Program> program) : mesh(std::move(mesh)),
        program(std::move(program)) {
        genVertexArrayBuffer();

        bindGeometry();

        saveBuffer();
    }

    Model::Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Program> program, std::shared_ptr<Material> material)
        : mesh(std::move(mesh)),
          program(std::move(program)),
          material(std::move(material)) {
        genVertexArrayBuffer();

        bindGeometry();
        bindTexture();

        saveBuffer();
    }

    void Model::genVertexArrayBuffer() {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
    }

    void Model::bindGeometry() const {
        glBindBuffer(GL_ARRAY_BUFFER, mesh->getVBO());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getEBO());
    }

    void Model::bindTexture() const {
        material->bindMaterial();
    }

    Model &Model::setProgram(std::shared_ptr<Program> prg) {
        program = prg;
        return *this;
    }

    void Model::saveBuffer() {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    //Set a new translation transformation vetor for the object.
    Model &Model::setTranslate(glm::vec3 axis) {
        translateAxis = axis;
        return *this;
    }

    Model &Model::setRotate(float deg, glm::vec3 axis) {
        rotateDeg = deg;
        rotateAxis = axis;
        return *this;
    }

    //Set a new scaling transformation vetor for the object.
    Model &Model::setScale(glm::vec3 axis) {
        scaleAxis = axis;
        return *this;
    }

    /*
        Draw function is called every frame in the main loop,
        applying the transformations of the object.
    */
    void Model::draw() {
        if (wireframe) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        (*program)
                .resetT()
                .translate(translateAxis)
                .rotate(rotateDeg, rotateAxis)
                .scale(scaleAxis)
                .use();

        material->bindMaterial();

        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, mesh->getIndexSize(), GL_UNSIGNED_INT, 0);
    }

    void Model::setWireframe(bool state) {
        wireframe = state;
    }

    GLuint Model::getID() const {
        return VAO;
    }
}
