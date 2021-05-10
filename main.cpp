#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include <shader/ShaderLoader.h>

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
            0.5f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f
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

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, (void*)0);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2, 0.5, 0.5, 1.0);

        auto rotate = (float)glm::radians(glfwGetTime()) * 10;
        glm::mat4 model(1.0);
        //model = glm::rotate(model, rotate, glm::vec3(0, 0, 1));

        glBindVertexArray(VAO);
        shader->Use();
        shader->SetUniformMatrix("model", model);
        //glDrawArrays(GL_TRIANGLES, 0, 6);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}