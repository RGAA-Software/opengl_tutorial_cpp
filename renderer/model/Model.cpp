#include "Model.h"


#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include <stb/stb_image.h>
#define STB_IMAGE_WRITE_STATIC
#include <stb/stb_image_write.h>

#include "Texture.h"

namespace sk {

Model::Model(const std::string &path, const std::string& vs_path, const std::string& fs_path)
    : IRenderer(vs_path, "", fs_path)
{
    LoadModel(path, true);
}


void Model::Render(float delta) {
    IRenderer::Render(delta);

    shader->SetUniform1i("diffuse_size", 1);

    for(unsigned int i = 0; i < meshes.size(); i++) {
        if (!meshes[i]) {
            continue;
        }

        auto idx = meshes[i]->GetMeshIndex();
        if (diffuse_textuers.find(idx) != diffuse_textuers.end()) {
            auto texture = diffuse_textuers.at(idx);
            shader->SetUniform1i("diffuse_size", 1);
            GLFunc glActiveTexture(GL_TEXTURE1);
            GLFunc glBindTexture(GL_TEXTURE_2D, texture->GetTexId());
            shader->SetUniform1i("diffuse[" + std::to_string(i) + "]", 1);
        }
        meshes[i]->Render(delta);
    }

    GLFunc glBindVertexArray(0);
}

void Model::LoadModel(const std::string& path, bool flip_uv) {
    Assimp::Importer importer;
    unsigned int flags = aiProcess_Triangulate
//            | aiProcess_GenSmoothNormals
            | aiProcess_GenNormals
            | aiProcess_CalcTangentSpace;
    if (flip_uv) {
        flags |= aiProcess_FlipUVs;
    }
    const aiScene* scene = importer.ReadFile(path, flags);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Load models failed : "<< path << " error : " << importer.GetErrorString() << std::endl;
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));

    ProcessNode(scene->mRootNode, scene);
}


void Model::ProcessNode(aiNode *node, const aiScene *scene) {
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh, scene));
    }

    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene);
    }

}

MeshPtr Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<TexturePtr> textures;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex{};
        glm::vec3 vector;

        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;

        if (mesh->HasNormals()) {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
        }

        if(mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.uv = vec;

            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.tangent = vector;

            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.bitangent = vector;
        } else {
            vertex.uv = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    mesh_count++;

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    std::vector<TexturePtr> diffuse_maps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());

    std::vector<TexturePtr> specular_maps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());

    std::vector<TexturePtr> normal_maps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normal_maps.begin(), normal_maps.end());

    std::vector<TexturePtr> height_maps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), height_maps.begin(), height_maps.end());

    std::cout << "Model, mesh , path : " << material->GetName().C_Str() << std::endl;

    return Mesh::Make(this, vertices, indices, textures, mesh_count);
}


std::vector<TexturePtr> Model::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName) {
    std::vector<TexturePtr> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);

        bool skip = false;
        for(unsigned int j = 0; j < textures_loaded.size(); j++) {
            if(std::strcmp(textures_loaded[j]->path.data(), str.C_Str()) == 0) {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if(!skip) {
            auto texture = TextureFromFile(str.C_Str(), this->directory);;
            if (aiTextureType_DIFFUSE == type) {
                texture->SetTexType(TextureType::kTexDiffuse);
                diffuse_textuers.insert(std::make_pair(mesh_count, texture));
            } else if (aiTextureType_SPECULAR == type) {
                texture->SetTexType(TextureType::kTexSpecular);
            } else if (aiTextureType_HEIGHT == type) {
                texture->SetTexType(TextureType::kTexNormal);
            }
            texture->type = typeName;
            texture->path = str.C_Str();
            textures.push_back(texture);
            if (texture->GetChannels() > 1) {
                textures_loaded.push_back(texture);
            }
        }
    }

    if (!textures.empty()) {
        if (aiTextureType_DIFFUSE == type) {
            diffuse_textuers.insert(std::make_pair(mesh_count, textures.at(0)));
        } else if (aiTextureType_SPECULAR == type) {

        } else if (aiTextureType_HEIGHT == type) {

        }
    }

    return textures;
}


TexturePtr Model::TextureFromFile(const char *path, const std::string& directory) {
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    GLuint texture_id;
    GLFunc glGenTextures(1, &texture_id);

    int width, height, channels;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &channels, 0);

    if (data) {
        GLenum format = GL_RGB;
        if (channels == 1) {
            format = GL_RED;
        } else if (channels == 3) {
            format = GL_RGB;
        } else if (channels == 4) {
            format = GL_RGBA;
        } else {
            std::cerr << "unknown format !!!" << std::endl;
        }

        GLFunc glBindTexture(GL_TEXTURE_2D, texture_id);
        GLFunc glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        GLFunc glGenerateMipmap(GL_TEXTURE_2D);

        GLFunc glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        GLFunc glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        GLFunc glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        GLFunc glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cerr << "Load texture failed : " << path << std::endl;
        stbi_image_free(data);
    }

    return Texture::Make(texture_id, width, height, channels);
}


}
