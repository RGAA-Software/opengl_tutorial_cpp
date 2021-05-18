//
// Created by chess on 2021/5/17.
//

#ifndef OPENGL_TUTORIAL_IRENDERER_H
#define OPENGL_TUTORIAL_IRENDERER_H

#include <string>
#include <memory>

#include "shader/ShaderLoader.h"

namespace sk {

class IRenderer {

public:
    IRenderer(const std::string &vs_path, const std::string &gs_path, const std::string &fs_path);
    virtual ~IRenderer();

protected:

    virtual void Render(float delta);


protected:
    ShaderPtr       shader;
    GLuint          vao;

};

}

#endif //OPENGL_TUTORIAL_IRENDERER_H
