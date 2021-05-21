#ifndef __MESH_H
#define __MESH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Vertex.h"

#include "gl_func_adapter.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <functional>

namespace sk {

class Model;
class ShaderProgram;
class Texture;

class Mesh {
public:

    static std::shared_ptr<Mesh> Make(
                               Model* attach_model,
                               const std::vector<Vertex>& vertices,
                               const std::vector<unsigned int>& indices,
                               const std::vector<std::shared_ptr<Texture>>& textures,
                               uint32_t idx);

    Mesh(Model* attach_model,
         const std::vector<Vertex>& vertices,
         const std::vector<unsigned int>& indices,
         const std::vector<std::shared_ptr<Texture>>& textures,
         uint32_t idx);


    void Render(float delta);

    void ExecInVAORegion(const std::function<void()>& task);

    uint32_t GetMeshIndex();

private:

    void InitMesh();

    std::vector<Vertex>          vertices;
    std::vector<unsigned int>    indices;
    std::vector<std::shared_ptr<Texture>>      textures;

    std::shared_ptr<ShaderProgram>  shader_program;

    GLuint                       render_vao;
    Model*                       attach_model;

    uint32_t                     mesh_idx;
};

typedef std::shared_ptr<Mesh> MeshPtr;

}
#endif
