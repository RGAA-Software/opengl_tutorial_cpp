//
// Created by chess on 2021/5/17.
//

#include "IRenderer.h"

#include "Director.h"

namespace sk {

IRenderer::IRenderer(const std::string &vs_path, const std::string &gs_path, const std::string &fs_path) {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // load shader
    shader = ShaderLoader::LoadShaderForPath(vs_path, fs_path);

}

IRenderer::~IRenderer() {

}

void IRenderer::SetTranslate(const glm::vec3& trans) {
    translate = trans;
}

void IRenderer::SetRotate(float angel, const glm::vec3& axis) {
    rotate_radian = glm::radians(angel);
    rotate_axis = axis;
}

void IRenderer::SetScale(const glm::vec3& scale) {
    this->scale = scale;
}

ShaderPtr IRenderer::GetShader() {
    return shader;
}

void IRenderer::Render(float delta) {
    glBindVertexArray(vao);
    shader->Use();

    glm::mat4 model(1.0);

    if (projection == Projection::kOrtho) {
        // do translation
        model = glm::translate(model, translate);
        //model = glm::translate(model, glm::vec3(size.x/2 * scale.x, size.y/2 * scale.y, 0));
        model = glm::rotate(model, rotate_radian, rotate_axis);
        model = glm::translate(model, glm::vec3(-size.x / 2 * scale.x, -size.y / 2 * scale.y, 0));
        model = glm::scale(model, scale);

        glm::mat4 view(1.0f);

        shader->SetUniformMatrix("model", model);
        shader->SetUniformMatrix("view", view);
        shader->SetUniformMatrix("projection", Director::Instance()->GetOrthoProjection());

    } else if (projection == Projection::kPerspective) {
        // do translation
        model = glm::translate(model, translate);
        model = glm::rotate(model, rotate_radian, rotate_axis);
        model = glm::scale(model, scale);

        shader->SetUniformMatrix("model", model);
        shader->SetUniformMatrix("view", Director::Instance()->GetCameraLookAt());
        shader->SetUniformMatrix("projection", Director::Instance()->GetPerspectiveProjection());
    }
}

}