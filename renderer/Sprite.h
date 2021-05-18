//
// Created by chess on 2021/5/17.
//

#ifndef OPENGL_TUTORIAL_SPRITE_H
#define OPENGL_TUTORIAL_SPRITE_H

#include "IRenderer.h"

#include <vector>

namespace sk {

enum class SpriteShape {
    kRect, kCircle
};

class Sprite : public IRenderer {
public:

    Sprite(const std::string& vs_path, const std::string& fs_path, SpriteShape shape = SpriteShape::kRect);
    ~Sprite();

    void Render(float delta) override;

private:

    GLuint                  texture;

    int                     circle_border = 50;
    std::vector<float>      circle_vertices;
    SpriteShape             shape = SpriteShape::kRect;
};

}

#endif //OPENGL_TUTORIAL_SPRITE_H
