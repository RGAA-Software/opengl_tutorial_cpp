
#ifndef OPENGL_VERTEX_H
#define OPENGL_VERTEX_H

#include <glm/glm.hpp>

namespace sk {

class Vertex {
public:

    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    glm::vec3 color;

    int xMeshIndex;
    int yMeshIndex;

};

}

#endif //OPENGL_VERTEX_H
