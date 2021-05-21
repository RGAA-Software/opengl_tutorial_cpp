//
// Created by huayang on 1/14/21.
//

#ifndef OPENGL_TEXTURELOADER_H
#define OPENGL_TEXTURELOADER_H

#include <memory>
#include <iostream>


#include "Texture.h"

namespace sk {

class TextureData {
public:

    TextureData(unsigned char* image_data, int width, int height, int channels)
        : data(image_data), width(width), height(height), channels(channels){
    }

    ~TextureData();

public:
    unsigned char* data;
    int width;
    int height;
    int channels;
};

typedef std::shared_ptr<TextureData> TexDataPtr;

class TextureLoader {
public:

    static TexDataPtr LoadTextureData(const std::string& path, bool flip = true);
    static TexturePtr LoadTexture(const std::string& path, int internal_format, bool flip = true);
};

}

#endif //OPENGL_TEXTURELOADER_H
