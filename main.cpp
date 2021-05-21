#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include <shader/ShaderLoader.h>
#include "renderer/Sprite.h"
#include "renderer/Director.h"
#include "renderer/MultiBars.h"
#include "renderer/Cube.h"

#include "InputProcessor.h"

using namespace sk;

int main(int argc, char** argv)
{
    // GLFW
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    float window_width = 1920;
    float window_height = 1080;
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_REFRESH_RATE, 60);
    glfwSwapInterval(0);
    window = glfwCreateWindow(window_width, window_height, "OpenGL Tutorial C++", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
        InputProcessor::Instance()->ProcessCursor(x, y);
    });

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
    //auto shader = ShaderLoader::LoadShaderForPath("../resources/shaders/triangle/vs.glsl", "../resources/shaders/triangle/fs.glsl");

    Director::Instance()->Init(window_width, window_height);
    Sprite sprite("../resources/shaders/triangle/vs.glsl", "../resources/shaders/triangle/fs_image_point_light.glsl", "../resources/images/ground_stone.jpg");
    //Sprite circle_sprite("../resources/shaders/triangle/vs.glsl", "../resources/shaders/triangle/fs.glsl", SpriteShape::kCircle, Projection::kOrtho);
    //MultiBars multi_bars("../resources/shaders/triangle/vs.glsl", "../resources/shaders/triangle/fs_color.glsl");

    Cube cube("../resources/shaders/triangle/vs.glsl", "../resources/shaders/triangle/fs_image_point_light.glsl","../resources/images/person.jpg");
    Cube light_cube("../resources/shaders/triangle/vs.glsl", "../resources/shaders/triangle/fs_uniform_color.glsl");

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::vec3 cube_positions[] = {
            glm::vec3(0, 0, -5),
            glm::vec3(1.0f, 0.6f, 0),
            glm::vec3(-2.0f, 1.0f, -3.0f),
            glm::vec3(3.0f, -0.8f, 1.0f),
            glm::vec3(-3.0f, -1.8f, -4.0f),
            glm::vec3(2.0f,  1.8f, -12.0f),
    };

    float sprite_scale = 1.0f;

    double lasttime = 0;
    double target_fps = 60;

    double last_render_time = 0;

    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1, 0.1, 0.1, 1.0);

        auto current_time = glfwGetTime();
        if (last_render_time == 0) {
            last_render_time = current_time;
        }
        float delta = current_time - last_render_time;
        last_render_time = current_time;

//        sprite.SetRotate(glfwGetTime()*16, glm::vec3(0,1,0));

        auto light_position = glm::vec3(0, -1, 0);
        auto light_color = glm::vec3(1,1,1);

        auto sprite_shader = sprite.GetShader();
        sprite_shader->Use();
        sprite_shader->SetUniform3fv("lightColor", light_color);
        sprite_shader->SetUniform3fv("lightPosition", light_position);
        sprite_shader->SetUniform3fv("cameraPosition", Director::Instance()->GetCameraPosition());
        sprite.SetRotate(-90, glm::vec3(1,0,0));
        sprite.SetScale(glm::vec3(1,1,1));
        sprite.SetTranslate(glm::vec3(-.3,-2,0));
        sprite.Render(0);

        auto light_cube_shader = light_cube.GetShader();
        light_cube_shader->Use();
        light_cube_shader->SetUniform3fv("color", light_color);
        light_cube.SetTranslate(light_position);
        light_cube.SetScale(glm::vec3(0.2));
        light_cube.Render(delta);

//        sprite.SetRotate(0);
//        sprite.SetScale(glm::vec3(1,1,1));
//        sprite.SetTranslate(glm::vec3(200, 200, 0));
//        sprite.Render(0);
//
//        sprite.SetTranslate(glm::vec3(400, 400, 0));
//        //sprite.SetRotate(glfwGetTime()*16);
//        sprite.SetScale(glm::vec3(sprite_scale, sprite_scale, 0));
//        sprite.Render(0);
//
//        circle_sprite.SetRotate(glfwGetTime()*16);
//        circle_sprite.SetTranslate(glm::vec3(600, 600, 0));
//        circle_sprite.Render(0);

        InputProcessor::Instance()->ProcessEvent(window, delta);

        glEnable(GL_DEPTH_TEST);
        auto cube_shader = cube.GetShader();
        cube_shader->Use();
        cube_shader->SetUniform3fv("lightColor", light_color);
        cube_shader->SetUniform3fv("lightPosition", light_position);
        cube_shader->SetUniform3fv("cameraPosition", Director::Instance()->GetCameraPosition());

        int index = 1;
        for (auto& pos : cube_positions) {
            index += 3;
            cube.SetTranslate(pos);
            cube.SetRotate(glfwGetTime()*index * (index%2 == 0 ? 1 : -1), glm::vec3(1,1,0));
            cube.Render(delta);
        }

        glDisable(GL_DEPTH_TEST);
//        multi_bars.Render(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();


        // other logic
        sprite_scale += 0.01;
        if (sprite_scale >= 2.5) {
            sprite_scale = 1.0f;
        }

        while (glfwGetTime() < lasttime + 1.0/target_fps) {
            // TODO: Put the thread to sleep, yield, or simply do nothing
        }
        lasttime += 1.0/target_fps;
    }

    glfwTerminate();
    return 0;
}