//
// Created by chess on 2021/5/17.
//

#include "Sprite.h"

#include "Director.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "stb/stb_image.h"

#include <vector>

namespace sk {

Sprite::Sprite(const std::string& vs_path, const std::string& fs_path, SpriteShape shape)
    : IRenderer(vs_path, "", fs_path) {

    this->shape = shape;

    // init my self

    float image_width = 200;
    float image_height = 200;

    size.x = image_width;
    size.y = image_height;

    float vertices[] = {
            0,  0,  0,                      1.0, 0.0, 0.0,    0.0f, 0.0f,
            image_width, 0,  0,             0.0, 1.0, 0.0,    1.0f, 0.0f,
            image_width, image_height, 0,   0.0, 0.0, 1.0,    1.0f, 1.0f,
            0,  image_height, 0,            0.9, 0.6, 0.8,    0.0f, 1.0f
    };


    auto insert_point_func = [&](float x, float y, float z, float r, float g, float b, float u, float v) {
        circle_vertices.push_back(x);
        circle_vertices.push_back(y);
        circle_vertices.push_back(z);

        circle_vertices.push_back(r);
        circle_vertices.push_back(g);
        circle_vertices.push_back(b);

        circle_vertices.push_back(u);
        circle_vertices.push_back(v);
    };

    // add circle center
    insert_point_func(image_width/2, image_height/2, 0,   0, 0, 0,  0.5, 0.5);
    float radius = 100;
    float item_angel = 360.0f/circle_border;
    for (int i = 0; i <= circle_border; i++) {
        float unit_x = glm::cos(glm::radians(item_angel*i));
        float unit_y = glm::sin(glm::radians(item_angel*i));

        insert_point_func(radius*(1+unit_x), radius*(1+unit_y), 0,   0, 0, 0,  (1+unit_x)/2, (1+unit_y)/2);
    }

    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    GLuint VBO;
    GLuint EBO;

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    if (shape == SpriteShape::kRect) {
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    } else if (shape == SpriteShape::kCircle) {
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*circle_vertices.size(), circle_vertices.data(), GL_STATIC_DRAW);
    }

    int stride = sizeof(float) * 8;
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, stride, (void*)(3*sizeof(float)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, false, stride, (void*)(6*sizeof(float)));

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // First Image
    // Gen Texture

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load Image
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("../resources/images/person.jpg", &width, &height, &channels, 0 );
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindVertexArray(0);
}

Sprite::~Sprite() {

}

void Sprite::Render(float delta) {
    IRenderer::Render(delta);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    shader->SetUniform1i("image", 0);

    if (shape == SpriteShape::kRect) {
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    } else if (shape == SpriteShape::kCircle) {
        glDrawArrays(GL_TRIANGLE_FAN, 0, circle_border+2);
    }
}

}