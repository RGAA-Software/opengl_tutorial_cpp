//
// Created by huayang on 1/13/21.
//

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include <stb/stb_image.h>
#define STB_IMAGE_WRITE_STATIC
#include <stb/stb_image_write.h>

#include <iostream>

namespace sk {

std::shared_ptr<Texture> Texture::Make(const std::string& path, bool flip) {
    return std::make_shared<Texture>(path, flip);
}

std::shared_ptr<Texture> Texture::Make(const std::string& path, int internal_format, bool flip) {
    return std::make_shared<Texture>(path, internal_format, flip);
}

std::shared_ptr<Texture> Texture::Make(const char* data, int width, int height, int internal_format) {
    return std::make_shared<Texture>(data, width, height, internal_format);
}

std::shared_ptr<Texture> Texture::Make(int id, int width, int height, int channels) {
    return std::make_shared<Texture>(id, width, height, channels);
}

Texture::Texture(int id, int width, int height, int channels) {
    this->id = id;
    this->width = width;
    this->height = height;
    this->channels = channels;
}


Texture::Texture(const std::string& path, bool flip) : Texture(path, -1, flip) {
}

Texture::Texture(const std::string& path, int internal_format, bool flip) {
    stbi_set_flip_vertically_on_load(flip);
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (internal_format == -1) {
        if (channels == 1) {
            internal_format = GL_R8;
        } else if (channels == 3) {
            internal_format = GL_RGB;
        } else if (channels == 4) {
            internal_format = GL_RGBA;
        }
    }
    InitTexture((const char*)data, width, height, internal_format);
    stbi_image_free(data);
}

Texture::Texture(const char* data, int width, int height, int internal_format) {
    InitTexture(data, width, height, internal_format);
}

void Texture::InitTexture(const char* data, int w, int h, int inner_format) {
    init = true;
    GLFunc glGenTextures(1, &id);
    GLFunc glBindTexture(GL_TEXTURE_2D, id);
    GLFunc glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    GLFunc glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    GLFunc glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    GLFunc glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    this->internal_format = inner_format;
    this->width = w;
    this->height = h;

    bool gamma_correction = false;
    GLenum bufferFormat = GL_RGB;
    if (internal_format == GL_RGB) {
        bufferFormat = gamma_correction ? GL_SRGB : GL_RGB;
        this->channels = 3;
    } else if (internal_format == GL_RGBA) {
        bufferFormat = gamma_correction ? GL_SRGB_ALPHA : GL_RGBA;
        this->channels = 4;
    } else if (internal_format == GL_R8) {
        bufferFormat = GL_RED;
        this->channels = 1;
    }

    //printf("sparrow , buffer format : %0x, internal format : %0x",internal_format, bufferFormat);

    this->format = bufferFormat;
    //this->format = internal_format;
    GLFunc glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    GLFunc glGenerateMipmap(GL_TEXTURE_2D);

    GLFunc glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
    if (init) {
        if (id != 0) {
            GLFunc glDeleteTextures(1, &id);
        }
    }
}

int Texture::GetTexId() {
    return this->id;
}

int Texture::GetTexWidth() {
    return width;
}

int Texture::GetTexHeight() {
    return height;
}

int Texture::GetChannels() {
    return channels;
}

GLenum Texture::GetInternalFormat() {
    return internal_format;
}

GLenum Texture::GetFormat() {
    return format;
}

void Texture::SetTexType(const TextureType &type) {
    tex_type = type;
}

TextureType Texture::GetTexType() {
    return tex_type;
}

void Texture::SetPath(const std::string &path) {
    this->path = path;
}

std::string Texture::GetPath() {
    return path;
}

}
