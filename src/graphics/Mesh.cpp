#include "Mesh.h"
#include <cassert>
#include <glad.h>

namespace oriongl::graphics {
Mesh::Mesh(vertex_array &vertexes, indexes_array &indexes) {
    genVertexArrayBuffer();
    genVertexBufferObject(vertexes);
    genElementBufferObject(indexes);
    bindBuffer();
}

void Mesh::genVertexBufferObject(const vertex_array &vertexes) {
    vertexesSize = vertexes.size();

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexesSize * sizeof(float), vertexes.data(), GL_STATIC_DRAW);
}

void Mesh::genElementBufferObject(const std::vector<uint> &indexes) {
    indexesSize = indexes.size();

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexesSize * sizeof(uint), indexes.data(), GL_STATIC_DRAW);
}

void Mesh::genVertexArrayBuffer() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
}

void Mesh::bindBuffer() {
    static_assert(sizeof(Vertex) == 32);
    static_assert(sizeof(Vertex::position) == 12);
    static_assert(sizeof(Vertex::normal) == 12);
    static_assert(sizeof(Vertex::text_coords) == 8);

    glVertexAttribPointer(0, sizeof(Vertex::position) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, sizeof(Vertex::normal) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, sizeof(Vertex::text_coords) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, text_coords));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

unsigned int Mesh::getVAO() const { return VAO; }

unsigned int Mesh::getVertexSize() const { return vertexesSize; }

unsigned int Mesh::getIndexSize() const { return indexesSize; }
} // namespace oriongl::graphics
