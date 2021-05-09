//
// Created by huayang on 7/3/19.
//

#ifndef OPENGL_SHADERLOADER_H
#define OPENGL_SHADERLOADER_H

#include "shader/ShaderProgram.h"
#include "gl_func_adapter.h"

#include <string>


namespace sk {

class ShaderLoader {

public:

    static ShaderPtr LoadShaderForPath(const std::string& v_gl_path, const std::string& f_gl_path);
    static ShaderPtr LoadShader(const std::string& v_gl, const std::string& f_gl);
    static ShaderPtr LoadShader(const std::string& v_gl, const std::string& g_gl, const std::string& f_gl);

private:


};

}

#endif //OPENGL_SHADERLOADER_H
