#pragma once
#include <vector>

namespace oriongl::core {
    using uint = unsigned int;

    typedef std::vector<float> vertex_array;
    typedef std::vector<uint> indexes_array;

    class Mesh {
        unsigned int vertexesSize = 0;
        unsigned int indexesSize = 0;
        uint VBO = 0;
        uint EBO = 0;

    public:
        Mesh(vertex_array &vertexes, indexes_array &indexes);

        uint getVBO() const;

        uint getEBO() const;

        unsigned int getVertexSize() const;

        unsigned int getIndexSize() const;

        void genVertexBufferObject(const vertex_array &vertexes);

        void genElementBufferObject(const indexes_array &indexes);
    };
}
