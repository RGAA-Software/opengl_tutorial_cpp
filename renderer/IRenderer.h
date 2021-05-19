//
// Created by chess on 2021/5/17.
//

#ifndef OPENGL_TUTORIAL_IRENDERER_H
#define OPENGL_TUTORIAL_IRENDERER_H

#include <string>
#include <memory>

#include "shader/ShaderLoader.h"

namespace sk {

enum class Projection {
    kOrtho, kPerspective
};

class IRenderer {

public:
    IRenderer(const std::string &vs_path, const std::string &gs_path, const std::string &fs_path);
    virtual ~IRenderer();

    void SetTranslate(const glm::vec3& trans);
    void SetRotate(float angel, const glm::vec3& axis = glm::vec3(0,0,1));
    void SetScale(const glm::vec3& scale);

protected:

    virtual void Render(float delta);


protected:
    ShaderPtr       shader;
    GLuint          vao;

    // Size
    glm::vec2       size = glm::vec2(0,0);

    // Transform
    glm::vec3       translate = glm::vec3(0,0,0);

    float           rotate_radian = 0;
    glm::vec3       rotate_axis = glm::vec3(0,0,1);

    glm::vec3       scale = glm::vec3(1,1,1);

    Projection      projection = Projection::kPerspective;
};

}

#endif //OPENGL_TUTORIAL_IRENDERER_H
