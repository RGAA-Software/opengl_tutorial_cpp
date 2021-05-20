//
// Created by chess on 2021/5/17.
//

#include "Director.h"

namespace sk {

void Director::Init(float width, float height) {

    ortho_projection = glm::ortho(0.0f, width, 0.0f, height, 0.0f, 1.0f);

    perspective_projection = glm::perspective(glm::radians(45.0f), width/height, 0.1f, 1000.0f);

    camera_pos = glm::vec3(0, 0, 10);
    camera_front = glm::vec3(0, 0, -1);
    camera_up = glm::vec3(0, 1, 0);
    camera_look_at = glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
}

glm::mat4 Director::GetOrthoProjection() {
    return ortho_projection;
}

glm::mat4 Director::GetPerspectiveProjection() {
    return perspective_projection;
}

glm::vec3 Director::GetCameraPosition() {
    return camera_pos;
}

void Director::UpdateCameraPosition(const glm::vec3& pos) {
    camera_pos = pos;
}

glm::vec3 Director::GetCameraFront() {
    return camera_front;
}

void Director::UpdateCameraFront(const glm::vec3& front) {
    camera_front = front;
}

glm::vec3 Director::GetCameraUp() {
    return camera_up;
}

glm::mat4 Director::GetCameraLookAt() {
    camera_look_at = glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
    return camera_look_at;
}

}