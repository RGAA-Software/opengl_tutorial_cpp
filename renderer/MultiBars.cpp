//
// Created by chess on 2021/5/18.
//

#include "MultiBars.h"

#include <vector>

namespace sk {

MultiBars::MultiBars(const std::string& vs_path, const std::string& fs_path)
    : IRenderer(vs_path, "", fs_path){

    // Init our data
    int bar_size = 30;
    int bar_gap = 3;
    int bar_width = 5;
    int bar_height = 200;

    glm::vec3 bottom_color = glm::vec3(1, 0.7, 0.3);
    glm::vec3 top_color = glm::vec3(0.3, 0.7, 1);

    std::vector<float> vertices;

    auto insert_point_func = [&](float x, float y, float z, float r, float g, float b) {
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);

        vertices.push_back(r);
        vertices.push_back(g);
        vertices.push_back(b);
    };

    for (int i = 0; i < bar_size; i++) {
        float left_bottom_x = i * (bar_width + bar_gap);
        float left_bottom_y = 0;

        float right_bottom_x = left_bottom_x + bar_width;
        float right_bottom_y = 0;

        float left_top_x = left_bottom_x;
        float left_top_y = bar_height;

        float right_top_x = right_bottom_x;
        float right_top_y = left_top_y;

        insert_point_func(left_bottom_x, left_bottom_y, 0, bottom_color.r, bottom_color.g, bottom_color.b);
        insert_point_func(right_bottom_x, right_bottom_y, 0, bottom_color.r, bottom_color.g, bottom_color.b);
        insert_point_func(left_top_x, left_top_y, 0, top_color.r, top_color.b, top_color.b);

        insert_point_func(right_bottom_x, right_bottom_y, 0, bottom_color.r, bottom_color.g, bottom_color.b);
        insert_point_func(right_top_x, right_top_y, 0, top_color.r, top_color.b, top_color.b);
        insert_point_func(left_top_x, left_top_y, 0, top_color.r, top_color.b, top_color.b);
    }

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 6* sizeof(float), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 6* sizeof(float), (void*)(3*sizeof(float)));

    glBindVertexArray(0);
}

MultiBars::~MultiBars() {

}

void MultiBars::Render(float delta) {
    IRenderer::Render(delta);

    glDrawArrays(GL_TRIANGLES, 0, 6 * 30);
}


}