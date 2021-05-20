//
// Created by chess on 2021/5/20.
//

#include "InputProcessor.h"
#include "renderer/Director.h"

#include <iostream>

namespace sk {

void InputProcessor::ProcessEvent(GLFWwindow *window, float delta) {

    auto director = Director::Instance();
    auto position = director->GetCameraPosition();
    auto front = director->GetCameraFront();
    auto up = director->GetCameraUp();
    auto speed = delta * 5;

    glm::vec3 camera_position;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera_position = position + front*speed;
        director->UpdateCameraPosition(camera_position);

    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera_position = position - front*speed;
        director->UpdateCameraPosition(camera_position);

    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        auto left_direction = glm::normalize(glm::cross(up, front));
        camera_position = position + left_direction * speed;
        director->UpdateCameraPosition(camera_position);

    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        auto left_direction = glm::normalize(glm::cross(up, front));
        camera_position = position - left_direction * speed;
        director->UpdateCameraPosition(camera_position);

    } else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera_position = position + glm::vec3(0, 1, 0)*speed;
        director->UpdateCameraPosition(camera_position);

    } else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera_position = position - glm::vec3(0, 1, 0)*speed;
        director->UpdateCameraPosition(camera_position);

    }
}

}