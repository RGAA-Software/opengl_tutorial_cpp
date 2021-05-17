#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include <shader/ShaderLoader.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "stb/stb_image.h"

using namespace sk;

ShaderPtr shader;

int main(int argc, char** argv)
{
    // GLFW
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "OpenGL Tutorial C++", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        std::cerr << "GLEW init error : " << glewGetErrorString(err) << std::endl;
        return -1;
    }

    std::cout <<"Status: Using GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    // Load Shader
    shader = ShaderLoader::LoadShaderForPath("../resources/shaders/triangle/vs.glsl", "../resources/shaders/triangle/fs.glsl");

    std::cout << "shader program id : " << shader->GetProgramId() << std::endl;



//    float vertices[] = {
//            0.5f, 0.5f, 0.0f,
//            0.5f, -0.5f, 0.0f,
//            -0.5f, 0.5f, 0.0f,
//
//            0.5f, -0.5f, 0.0f,
//            -0.5f, -0.5f, 0.0f,
//            -0.5f, 0.5f, 0.0f,
//    };

    float vertices[] = {
            0.5f, 0.5f, 0.0f,       1.0, 0.0, 0.0,    1.0f, 1.0f,
            0.5f, -0.5f, 0.0f,      0.0, 1.0, 0.0,    1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,     0.0, 0.0, 1.0,    0.0f, 0.0f,
            -0.5f, 0.5f, 0.0f,      0.9, 0.6, 0.8,     0.0f, 1.0f
    };

    unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
    };

    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    int stride = sizeof(float) * 8;
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, stride, (void*)(3*sizeof(float)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, false, stride, (void*)(6*sizeof(float)));

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // First Image
    // Gen Texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load Image
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("../resources/images/person.jpg", &width, &height, &channels, 0 );
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Second Image
    // Gen Texture
    GLuint texture_logo;
    glGenTextures(1, &texture_logo);
    glBindTexture(GL_TEXTURE_2D, texture_logo);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load Image
    int logo_width, logo_height, logo_channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* logo_data = stbi_load("../resources/images/logo_big.png", &logo_width, &logo_height, &logo_channels, 0 );
    if (logo_data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, logo_data);
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    glBindVertexArray(0);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2, 0.5, 0.5, 1.0);


        auto rotate = (float)glm::radians(glfwGetTime()) * 10;
        glm::mat4 model(1.0);
        model = glm::translate(model, glm::vec3(0.5, 0, 0));
        //model = glm::rotate(model, rotate, glm::vec3(0, 0, 1));

        glBindVertexArray(VAO);
        shader->Use();
        shader->SetUniformMatrix("model", model);
        //glDrawArrays(GL_TRIANGLES, 0, 6);

        float red_value = (float)glm::sin(glfwGetTime());
        glm::vec3 color(red_value, red_value/2, red_value/2);
        shader->SetUniform3fv("color", color);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        shader->SetUniform1i("image", 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture_logo);
        shader->SetUniform1i("image2", 1);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}