//
// Created by chess on 2021/5/17.
//

#include "IRenderer.h"

namespace sk {

IRenderer::IRenderer(const std::string &vs_path, const std::string &gs_path, const std::string &fs_path) {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // load shader
    shader = ShaderLoader::LoadShaderForPath(vs_path, fs_path);

}

IRenderer::~IRenderer() {

}

void IRenderer::Render(float delta) {
    glBindVertexArray(vao);
    shader->Use();
}

}