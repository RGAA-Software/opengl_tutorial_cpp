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

void InputProcessor::ProcessCursor(double x, double y) {
    //std::cout << "x : " << x << " y : " << y << std::endl;
    if (first_enter) {
        first_enter = false;
        last_x = x;
        last_y = y;
        return;
    }

    float delta_x = x - last_x;
    float delta_y = - (y - last_y);

    last_x = x;
    last_y = y;

    float sense = 0.02;
    delta_x *= sense;
    delta_y *= sense;

    pitch += delta_y;
    yaw += delta_x;

    if (pitch > 89) {
        pitch = 89;
    } else if (pitch < -89) {
        pitch = -89;
    }

    glm::vec3 front;
    front.x = glm::cos(glm::radians(pitch)) * glm::cos(glm::radians(yaw));
    front.y = glm::sin(glm::radians(pitch));
    front.z = glm::cos(glm::radians(pitch)) * glm::sin(glm::radians(yaw));

    Director::Instance()->UpdateCameraFront(glm::normalize(front));
}

}