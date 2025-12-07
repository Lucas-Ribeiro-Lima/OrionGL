#include "Mesh.h"
#include <glad.h>

namespace oriongl::core {
    Mesh::Mesh(vertex_array &vertexes, indexes_array &indexes) {
        genVertexBufferObject(vertexes);
        genElementBufferObject(indexes);
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

    GLuint Mesh::getVBO() const {
        return VBO;
    }

    GLuint Mesh::getEBO() const {
        return EBO;
    }

    unsigned int Mesh::getVertexSize() const {
        return vertexesSize;
    }

    unsigned int Mesh::getIndexSize() const {
        return indexesSize;
    }
}
