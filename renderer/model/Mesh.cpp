#include "Mesh.h"

#include "Model.h"
#include "Texture.h"


namespace sk {


std::shared_ptr<Mesh> Mesh::Make(
                           Model* attach_model,
                           const std::vector<Vertex>& vertices,
                           const std::vector<unsigned int>& indices,
                           const std::vector<TexturePtr>& textures,
                           uint32_t idx) {
    return std::make_shared<Mesh>(attach_model, vertices, indices, textures, idx);
}


Mesh::Mesh(Model* attach_model,
           const std::vector<Vertex>& vertices,
           const std::vector<unsigned int>& indices,
           const std::vector<TexturePtr>& textures,
           uint32_t idx) {
    this->attach_model = attach_model;
    shader_program = attach_model->GetShader();
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    mesh_idx = idx;
    InitMesh();
}

void Mesh::InitMesh() {

    GLuint vertex_buffer;
    GLuint element_buffer;

    GLFunc glGenVertexArrays(1, &render_vao);
    GLFunc glBindVertexArray(render_vao);

    GLFunc glGenBuffers(1, &vertex_buffer);
    GLFunc glGenBuffers(1, &element_buffer);


    GLFunc glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    GLFunc glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    GLFunc glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
    GLFunc glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    auto pos_loc = shader_program->GetAttribLocation("aPos");
    GLFunc glEnableVertexAttribArray(pos_loc);
    GLFunc glVertexAttribPointer(pos_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    auto normal_loc = shader_program->GetAttribLocation("aNormal");
    GLFunc glEnableVertexAttribArray(normal_loc);
    GLFunc glVertexAttribPointer(normal_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    auto tex_loc = shader_program->GetAttribLocation("aTex");
    GLFunc glEnableVertexAttribArray(tex_loc);
    GLFunc glVertexAttribPointer(tex_loc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    auto tangent_loc = shader_program->GetAttribLocation("aTangent");
    GLFunc glEnableVertexAttribArray(tangent_loc);
    GLFunc glVertexAttribPointer(tangent_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

    auto bitangent_loc = shader_program->GetAttribLocation("aBiTangent");
    GLFunc glEnableVertexAttribArray(bitangent_loc);
    GLFunc glVertexAttribPointer(bitangent_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

    GLFunc glBindBuffer(GL_ARRAY_BUFFER, 0);
    GLFunc glBindVertexArray(0);
}

void Mesh::ExecInVAORegion(const std::function<void ()> &task) {
    GLFunc glBindVertexArray(render_vao);
    task();
    GLFunc glBindVertexArray(0);
}

uint32_t Mesh::GetMeshIndex() {
    return mesh_idx;
}

void Mesh::Render(float delta) {
    GLFunc glBindVertexArray(render_vao);
    GLFunc glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    GLFunc glBindVertexArray(0);
}


}
