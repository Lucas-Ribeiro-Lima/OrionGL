#include "Model.h"
#include <cassert>
#include <glad.h>

namespace oriongl::graphics {
Model::Model(std::shared_ptr<Program> program) : program(std::move(program)) {}

std::shared_ptr<Program> Model::getModelProgram() const { return program; }

void Model::setProgram(std::shared_ptr<Program> prg) { program = prg; }

void Model::loadData(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material) {
    meshes.push_back(std::move(mesh));
    materials.push_back(std::move(material));
}

void Model::deleteData(size_t index) {
    assert(index < meshes.size() && "Index out of bounds in Model::deleteData");
    meshes.erase(meshes.begin() + index);
    materials.erase(materials.begin() + index);
}

/*
    Draw function is called every frame in the main loop,
    applying the transformations of the object.
*/
void Model::draw() {
    for (size_t i = 0; i < meshes.size(); i++) {
        glBindVertexArray(meshes[i]->getVAO());

        if (materials[i])
            materials[i]->bindMaterial();

        glDrawElements(GL_TRIANGLES, meshes[i]->getIndexSize(), GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
    }
}
} // namespace oriongl::graphics
