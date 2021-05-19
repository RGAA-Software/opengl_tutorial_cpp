//
// Created by chess on 2021/5/17.
//

#include "Director.h"

namespace sk {

void Director::Init(float width, float height) {

    ortho_projection = glm::ortho(0.0f, width, 0.0f, height, 0.0f, 1.0f);

    perspective_projection = glm::perspective(glm::radians(45.0f), width/height, 0.1f, 1000.0f);
    camera_look_at = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0,0,0), glm::vec3(0,1,0));
}

glm::mat4 Director::GetOrthoProjection() {
    return ortho_projection;
}

glm::mat4 Director::GetPerspectiveProjection() {
    return perspective_projection;
}

glm::mat4 Director::GetCameraLookAt() {
    return camera_look_at;
}

}