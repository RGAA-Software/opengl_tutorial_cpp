//
// Created by chess on 2021/5/17.
//

#ifndef OPENGL_TUTORIAL_SPRITE_H
#define OPENGL_TUTORIAL_SPRITE_H

#include "IRenderer.h"

namespace sk {


class Sprite : public IRenderer {
public:

    Sprite(const std::string& vs_path, const std::string& fs_path);
    ~Sprite();

    void Render(float delta) override;

private:

    GLuint          texture;
};

}

#endif //OPENGL_TUTORIAL_SPRITE_H
