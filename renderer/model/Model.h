#ifndef _RENDER_MODEL_H
#define _RENDER_MODEL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "gl_func_adapter.h"

#include "renderer/IRenderer.h"

namespace sk {

class Texture;

struct ModelTransform {

    ModelTransform(const glm::vec3& t, const glm::vec3& r, const glm::vec3& s) {
        this->translate = t;
        this->rotate = r;
        this->scale = s;
    }

    glm::vec3 translate;
    glm::vec3 rotate;
    glm::vec3 scale;
};


class Model : public IRenderer {
public:

    Model(const std::string &path, const std::string& vs_path, const std::string& fs_path);

    void Render(float delta) override;

private:

    std::shared_ptr<Texture> TextureFromFile(const char *path, const std::string& directory);

    void LoadModel(const std::string& path, bool flip_uv);

    void ProcessNode(aiNode *node, const aiScene *scene);

    MeshPtr ProcessMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<std::shared_ptr<Texture>> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName);

private:

    std::map<uint32_t, std::shared_ptr<Texture>> diffuse_textuers;
    std::vector<std::shared_ptr<Texture>> textures_loaded;
    std::vector<MeshPtr>    meshes;
    std::string directory;

//    bool use_attach_color = false;
//    glm::vec3 attach_color;

//    int         instance_count = 0;
//    GLuint      instance_buffer;
//    int         instance = 0;
//    std::vector<glm::mat4>   instance_models;

    uint32_t    mesh_count = 0;
};




typedef std::shared_ptr<Model> ModelPtr;

}


#endif
