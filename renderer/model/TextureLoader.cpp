//
// Created by huayang on 1/14/21.
//

#include "TextureLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include <stb/stb_image.h>
#define STB_IMAGE_WRITE_STATIC
#include <stb/stb_image_write.h>

namespace sk {

TextureData::~TextureData() {
    if (data) {
        stbi_image_free(data);
    }
}

TexDataPtr TextureLoader::LoadTextureData(const std::string& path, bool flip) {
    stbi_set_flip_vertically_on_load(flip);
    int width = 0, height = 0, channels = 0;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    auto result = std::make_shared<TextureData>(data, width, height, channels);
    return result;
}

TexturePtr TextureLoader::LoadTexture(const std::string& path, int internal_format, bool flip) {
    return Texture::Make(path, internal_format, flip);
}

}
