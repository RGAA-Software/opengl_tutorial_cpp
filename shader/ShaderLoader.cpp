//
// Created by huayang on 7/3/19.
//

#include "ShaderLoader.h"
#include <vector>
#include <string>
#include <fstream>
#include <ostream>
#include <sstream>
#include <iostream>

namespace sk {

ShaderPtr ShaderLoader::LoadShaderForPath(const std::string &v_gl_path, const std::string &f_gl_path) {
    // Read the Vertex Shader code from the file
    std::string vertex_shader_code;
    std::ifstream vertex_shader_stream(v_gl_path, std::ios::in);
    if (vertex_shader_stream.is_open()) {
        std::stringstream sstr;
        sstr << vertex_shader_stream.rdbuf();
        vertex_shader_code = sstr.str();
        vertex_shader_stream.close();
    } else {
        std::cerr << "failed to open : " << v_gl_path << std::endl;
        return nullptr;
    }

    // Read the Fragment Shader code from the file
    std::string fragment_shader_code;
    std::ifstream fragment_shader_stream(f_gl_path, std::ios::in);
    if (fragment_shader_stream.is_open()) {
        std::stringstream sstr;
        sstr << fragment_shader_stream.rdbuf();
        fragment_shader_code = sstr.str();
        fragment_shader_stream.close();
    } else {
        std::cerr << "failed to open : " << v_gl_path << std::endl;
        return nullptr;
    }

    return LoadShader(vertex_shader_code, fragment_shader_code);
}

ShaderPtr ShaderLoader::LoadShader(const std::string& v_gl, const std::string& g_gl, const std::string& f_gl) {
    auto result = std::make_shared<ShaderProgram>();
    GLint compile_result = GL_FALSE;
    int log_len;

    // Create the shaders
    GLuint vertex_shader_id = GLFunc glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader_id = GLFunc glCreateShader(GL_FRAGMENT_SHADER);
    GLuint geometry_shader_id = GLFunc glCreateShader(GL_GEOMETRY_SHADER);

    // Compile Vertex Shader
    char const *vertex_source = v_gl.c_str();
    GLFunc glShaderSource(vertex_shader_id, 1, &vertex_source, NULL);
    GLFunc glCompileShader(vertex_shader_id);

    // Check Vertex Shader
    GLFunc glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &compile_result);
    GLFunc glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &log_len);
    if (log_len > 0) {
        std::vector<char> err_msg(log_len + 1);
        GLFunc glGetShaderInfoLog(vertex_shader_id, log_len, NULL, &err_msg[0]);
        printf("%s\n", &err_msg[0]);
    }

    if (!g_gl.empty()) {
        // Compile Geometry Shader
        char const *geometry_source = g_gl.c_str();
        GLFunc glShaderSource(geometry_shader_id, 1, &geometry_source, NULL);
        GLFunc glCompileShader(geometry_shader_id);

        // Check Vertex Shader
        GLFunc glGetShaderiv(geometry_shader_id, GL_COMPILE_STATUS, &compile_result);
        GLFunc glGetShaderiv(geometry_shader_id, GL_INFO_LOG_LENGTH, &log_len);
        if (log_len > 0) {
            std::vector<char> err_msg(log_len + 1);
            GLFunc glGetShaderInfoLog(geometry_shader_id, log_len, NULL, &err_msg[0]);
            printf("%s\n", &err_msg[0]);
        }
    }

    // Compile Fragment Shader
    char const *fragment_source = f_gl.c_str();
    GLFunc glShaderSource(fragment_shader_id, 1, &fragment_source, NULL);
    GLFunc glCompileShader(fragment_shader_id);

    // Check Fragment Shader
    GLFunc glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &compile_result);
    GLFunc glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &log_len);
    if (log_len > 0) {
        std::vector<char> err_msg(log_len + 1);
        GLFunc glGetShaderInfoLog(fragment_shader_id, log_len, NULL, &err_msg[0]);
        printf("%s\n", &err_msg[0]);
    }

    // Link the program
    GLuint program_id = GLFunc glCreateProgram();
    GLFunc glAttachShader(program_id, vertex_shader_id);
    if (!g_gl.empty()) {
        GLFunc glAttachShader(program_id, geometry_shader_id);
    }
    GLFunc glAttachShader(program_id, fragment_shader_id);
    GLFunc glLinkProgram(program_id);

    // Check the program
    GLFunc glGetProgramiv(program_id, GL_LINK_STATUS, &compile_result);
    GLFunc glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_len);
    if (log_len > 0) {
        std::vector<char> err_msg(log_len + 1);
        GLFunc glGetProgramInfoLog(program_id, log_len, NULL, &err_msg[0]);
        printf("%s\n", &err_msg[0]);
    }

    GLFunc glDetachShader(program_id, vertex_shader_id);
    GLFunc glDetachShader(program_id, fragment_shader_id);
    GLFunc glDetachShader(program_id, geometry_shader_id);

    GLFunc glDeleteShader(vertex_shader_id);
    GLFunc glDeleteShader(fragment_shader_id);
    GLFunc glDeleteShader(geometry_shader_id);

    result->program_id = program_id;
    return result;
}

ShaderPtr ShaderLoader::LoadShader(const std::string &v_gl, const std::string &f_gl) {
    return LoadShader(v_gl, "", f_gl);
}

}
