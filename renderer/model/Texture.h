//
// Created by huayang on 1/13/21.
//

#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include <string>
#include <memory>

#include "gl_func_adapter.h"

namespace sk {

enum class TextureType {
    kTexNone, kTexDiffuse, kTexSpecular, kTexNormal,
};

class Texture {
public:
    Texture() = default;
    Texture(int id, int width, int height, int channels = 3);
    Texture(const std::string& path, bool flip);
    Texture(const std::string& path, int internal_format, bool flip);
    Texture(const char* data, int width, int height, int internal_format);
    ~Texture();

    static std::shared_ptr<Texture> Make(const std::string& path, bool flip);
    static std::shared_ptr<Texture> Make(const std::string& path, int type, bool flip);
    static std::shared_ptr<Texture> Make(const char* data, int width, int height, int internal_format);
    static std::shared_ptr<Texture> Make(int id, int width, int height, int channels);

    int GetTexId();
    int GetTexWidth();
    int GetTexHeight();
    int GetChannels();

    GLenum GetInternalFormat();
    GLenum GetFormat();

    void SetTexType(const TextureType& type);
    TextureType GetTexType();

    void SetPath(const std::string& path);
    std::string GetPath();

private:

    void InitTexture(const char* data, int w, int h, int inner_format);
    bool init = false;

    int width = 0;
    int height = 0;
    int channels = 0;

    GLenum format;
    GLenum internal_format;

    TextureType tex_type = TextureType::kTexNone;

public:
    GLuint id = 0;

    std::string type;
    std::string path;
};


typedef std::shared_ptr<Texture> TexturePtr;
}

#endif //OPENGL_TEXTURE_H
