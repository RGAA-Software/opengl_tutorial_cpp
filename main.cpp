#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include <shader/ShaderLoader.h>
#include "renderer/Sprite.h"
#include "renderer/Director.h"

using namespace sk;

ShaderPtr shader;

glm::mat4 projection;

int main(int argc, char** argv)
{
    // GLFW
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    float window_width = 800;
    float window_height = 800;
    glfwWindowHint(GLFW_SAMPLES, 4);
    window = glfwCreateWindow(window_width, window_height, "OpenGL Tutorial C++", NULL, NULL);
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

    Director::Instance()->Init(window_width, window_height);
    Sprite sprite("../resources/shaders/triangle/vs.glsl", "../resources/shaders/triangle/fs.glsl");
    Sprite circle_sprite("../resources/shaders/triangle/vs.glsl", "../resources/shaders/triangle/fs.glsl", SpriteShape::kCircle);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float sprite_scale = 1.0f;

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2, 0.5, 0.5, 1.0);

        sprite.SetRotate(0);
        sprite.SetScale(glm::vec3(1,1,1));
        sprite.SetTranslate(glm::vec3(0,0,0));
        //sprite.Render(0);

        sprite.SetRotate(0);
        sprite.SetScale(glm::vec3(1,1,1));
        sprite.SetTranslate(glm::vec3(200, 200, 0));
        //sprite.Render(0);

        sprite.SetTranslate(glm::vec3(400, 400, 0));
        //sprite.SetRotate(glfwGetTime()*16);
        sprite.SetScale(glm::vec3(sprite_scale, sprite_scale, 0));
        //sprite.Render(0);

        circle_sprite.SetTranslate(glm::vec3(600, 600, 0));
        circle_sprite.Render(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();


        // other logic
        sprite_scale += 0.0001;
        if (sprite_scale >= 2.5) {
            sprite_scale = 1.0f;
        }
    }

    glfwTerminate();
    return 0;
}