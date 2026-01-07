#include "Model.h"
#include <cassert>
#include <glad.h>

namespace oriongl::graphics {
Model::Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Program> program) : program(std::move(program)) {
    meshes.push_back(std::move(mesh));
    materials.push_back(nullptr);
}

Model::Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Program> program, std::shared_ptr<Material> material)
    : program(std::move(program)) {
    meshes.push_back(std::move(mesh));
    materials.push_back(std::move(material));
}

Model &Model::setProgram(std::shared_ptr<Program> prg) {
    program = prg;
    return *this;
}

// Set a new translation transformation vetor for the object.
Model &Model::setTranslate(glm::vec3 axis) {
    data.position = axis;
    return *this;
}

Model &Model::setRotate(float deg, glm::vec3 axis) {
    data.rotate_deg = deg;
    data.rotate_axis = axis;
    return *this;
}

// Set a new scaling transformation vetor for the object.
Model &Model::setScale(glm::vec3 axis) {
    data.scale_axis = axis;
    return *this;
}

/*
    Draw function is called every frame in the main loop,
    applying the transformations of the object.
*/
void Model::draw() {
    (*program).resetT().translate(data.position).rotate(data.rotate_deg, data.rotate_axis).scale(data.scale_axis).use();

    for (size_t i = 0; i < meshes.size(); i++) {
        glBindVertexArray(meshes[i]->getVAO());

        if (materials[i])
            materials[i]->bindMaterial();

        glDrawElements(GL_TRIANGLES, meshes[i]->getIndexSize(), GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
    }
}
} // namespace oriongl::graphics
