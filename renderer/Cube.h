//
// Created by chess on 2021/5/19.
//

#ifndef OPENGL_TUTORIAL_CUBE_H
#define OPENGL_TUTORIAL_CUBE_H

#include "IRenderer.h"

namespace sk {

class Cube : public IRenderer {
public:

    Cube(const std::string& vs_path, const std::string& fs_path, const std::string& tex_path = "");
    ~Cube();

    void Render(float delta) override;

private:
    float vertex[8*36] = {
        -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
        0.5f, 0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
        0.5f, 0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f,   0.0f,  0.0f,  1.0f,    0.0f, 0.0f,
        0.5f, -0.5f, 0.5f,   0.0f,  0.0f,  1.0f,    1.0f, 0.0f,
        0.5f, 0.5f, 0.5f,    0.0f,  0.0f,  1.0f,    1.0f, 1.0f,
        0.5f, 0.5f, 0.5f,    0.0f,  0.0f,  1.0f,    1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f,    0.0f,  0.0f,  1.0f,    0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,   0.0f,  0.0f,  1.0f,    0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f,   -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,  -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f,   -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,

        0.5f, 0.5f, 0.5f,    1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
        0.5f, 0.5f, -0.5f,   1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
        0.5f, -0.5f, 0.5f,   1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
        0.5f, 0.5f, 0.5f,    1.0f,  0.0f,  0.0f,    1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f,
        0.5f, -0.5f, 0.5f,    0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
        0.5f, -0.5f, 0.5f,    0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,    0.0f, -1.0f,  0.0f,   0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f,
        0.5f, 0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 1.0f,
        0.5f, 0.5f, 0.5f,    0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
        0.5f, 0.5f, 0.5f,    0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f,    0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f,   0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    GLuint texture;
};

}

#endif //OPENGL_TUTORIAL_CUBE_H
