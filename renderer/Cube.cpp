//
// Created by chess on 2021/5/19.
//

#include "Cube.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "stb/stb_image.h"

namespace sk {

Cube::Cube(const std::string& vs_path, const std::string& fs_path, const std::string& tex_path)
    : IRenderer(vs_path, "", fs_path) {

    int stride = 8;
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), &vertex[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride*sizeof(float), 0);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, false, stride*sizeof(float), (void*)(6*sizeof(float)));

    if (!tex_path.empty()) {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        int width, height, channels;
        unsigned char* data = stbi_load(tex_path.c_str(), &width, &height, &channels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    glBindVertexArray(0);
}

Cube::~Cube() {

}

void Cube::Render(float delta) {
    IRenderer::Render(delta);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    shader->SetUniform1i("image", 0);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

}