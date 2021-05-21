#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include <shader/ShaderLoader.h>
#include "renderer/Sprite.h"
#include "renderer/Director.h"
#include "renderer/MultiBars.h"
#include "renderer/Cube.h"
#include "renderer/model/Model.h"

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
    Sprite sprite("../resources/shaders/triangle/vs.glsl", "../resources/shaders/triangle/fs_image_spot_light.glsl", "../resources/images/ground_stone.jpg");
    //Sprite circle_sprite("../resources/shaders/triangle/vs.glsl", "../resources/shaders/triangle/fs.glsl", SpriteShape::kCircle, Projection::kOrtho);
    //MultiBars multi_bars("../resources/shaders/triangle/vs.glsl", "../resources/shaders/triangle/fs_color.glsl");

    Cube cube("../resources/shaders/triangle/vs.glsl", "../resources/shaders/triangle/fs_image_directional_light.glsl","../resources/images/person.jpg");
    Cube light_cube("../resources/shaders/triangle/vs.glsl", "../resources/shaders/triangle/fs_uniform_color.glsl");

    //Model model("../resources/models/earth/earth.obj", "../resources/shaders/triangle/vs.glsl", "../resources/shaders/triangle/fs_model.glsl");
    Model model("../resources/models/nanosuit/nanosuit.obj",
                "../resources/shaders/triangle/vs.glsl",
                "../resources/shaders/triangle/fs_model.glsl");
    Model model_earth("../resources/models/earth/earth.obj",
                "../resources/shaders/triangle/vs.glsl",
                "../resources/shaders/triangle/fs_model.glsl");
    Model model_statue("../resources/models/statue/12328_Statue_v1_L2.obj",
                "../resources/shaders/triangle/vs.glsl",
                "../resources/shaders/triangle/fs_model.glsl");

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::vec3 cube_positions[] = {
            glm::vec3(0, 3, -5),
            glm::vec3(2.0f, 0.6f, 0),
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
        glEnable(GL_DEPTH_TEST);

        auto current_time = glfwGetTime();
        if (last_render_time == 0) {
            last_render_time = current_time;
        }
        float delta = current_time - last_render_time;
        last_render_time = current_time;

//        sprite.SetRotate(glfwGetTime()*16, glm::vec3(0,1,0));

        auto light_direction = glm::vec3(-0.5, -1, 0);
        auto light_color = glm::vec3(1.0,1.0,1.0);
        auto light_position = glm::vec3(2, 1, 0);

        auto sprite_shader = sprite.GetShader();
        sprite_shader->Use();
        sprite_shader->SetUniform3fv("lightColor", light_color);
        sprite_shader->SetUniform3fv("lightDirection", light_direction);
        sprite_shader->SetUniform1f("lightCutoffAngel", glm::cos(glm::radians(15.0f)));
        sprite_shader->SetUniform1f("lightOuterCutoffAngel", glm::cos(glm::radians(25.0f)));
        sprite_shader->SetUniform3fv("lightPosition", light_position);
        sprite_shader->SetUniform3fv("cameraPosition", Director::Instance()->GetCameraPosition());
        sprite.SetRotate(-90, glm::vec3(1,0,0));
        sprite.SetScale(glm::vec3(1,1,1));
        sprite.SetTranslate(glm::vec3(0,-2,0));
        sprite.Render(0);

        auto light_cube_shader = light_cube.GetShader();
        light_cube_shader->Use();
        light_cube_shader->SetUniform3fv("color", light_color);
        light_cube.SetTranslate(light_position);
        light_cube.SetScale(glm::vec3(0.1));
        light_cube.Render(delta);

        float earth_scale = 0.0025;
        auto model_earth_shader = model_earth.GetShader();
        model_earth_shader->Use();
        model_earth_shader->SetUniform3fv("lightColor", light_color);
        model_earth_shader->SetUniform3fv("lightDirection", light_direction);
        model_earth.SetRotate(glfwGetTime()*16, glm::vec3(0,1,0));
        model_earth.SetScale(glm::vec3(earth_scale, earth_scale, earth_scale));
        model_earth.SetTranslate(glm::vec3(3, 1, -1));
        model_earth.Render(delta);

        float scale = 0.20;
        auto model_shader = model.GetShader();
        model_shader->Use();
        model_shader->SetUniform3fv("lightColor", light_color);
        model_shader->SetUniform3fv("lightDirection", light_direction);
        model.SetRotate(glfwGetTime()*16, glm::vec3(0,1,0));
        model.SetScale(glm::vec3(scale, scale, scale));
        model.SetTranslate(glm::vec3(0, -1, 0));
        model.Render(delta);

        float statue_scale = 0.015;
        auto model_statue_shader = model_statue.GetShader();
        model_statue_shader->Use();
        model_statue_shader->SetUniform3fv("lightColor", light_color);
        model_statue_shader->SetUniform3fv("lightDirection", light_direction);
        model_statue.SetTranslate(glm::vec3(-3, -2, 0));
        model_statue.SetScale(glm::vec3(statue_scale,statue_scale,statue_scale));
        model_statue.SetRotate(-90, glm::vec3(1,0,0));
        model_statue.Render(delta);


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


        auto cube_shader = cube.GetShader();
        cube_shader->Use();
        cube_shader->SetUniform3fv("lightColor", light_color);
        cube_shader->SetUniform3fv("lightDirection", light_direction);
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