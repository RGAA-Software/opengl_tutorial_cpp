//
// Created by huayang on 7/3/19.
//

#ifndef OPENGL_SHADERPROGRAM_H
#define OPENGL_SHADERPROGRAM_H

#include "gl_func_adapter.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>
#include <string>

namespace sk {

class ShaderProgram {

public:

    void Use() {
        GLFunc glUseProgram(program_id);
    }

    void Release() {
        GLFunc glUseProgram(0);
    }

    int GetAttribLocation(const std::string& name) {
        return GLFunc glGetAttribLocation(program_id, name.c_str());
    }

    int GetUniformLocation(const std::string& name) {
        return GLFunc glGetUniformLocation(program_id, name.c_str());
    }

    void SetUniform1i(const std::string& name, int value) {
        GLFunc glUniform1i(GetUniformLocation(name), value);
    }

    void SetUniform1f(const std::string& name, float value) {
        GLFunc glUniform1f(GetUniformLocation(name), value);
    }

    void SetUniform2fv(const std::string& name, const glm::vec2& vec) {
        GLFunc glUniform2f(GetUniformLocation(name), vec.x, vec.y);
    }

    void SetUniform3fv(const std::string& name, const glm::vec3& vec) {
        GLFunc glUniform3f(GetUniformLocation(name), vec.x, vec.y, vec.z);
    }

    void SetUniformMatrix(const std::string& name, const glm::mat4& m) {
        auto loc = GetUniformLocation(name);
        GLFunc glUniformMatrix4fv(loc, 1, false, glm::value_ptr(m));
    }

    int GetProgramId() {
        return program_id;
    }

public:
  int program_id;


private:

};

typedef std::shared_ptr<ShaderProgram> ShaderPtr;

}

#endif //OPENGL_SHADERPROGRAM_H
