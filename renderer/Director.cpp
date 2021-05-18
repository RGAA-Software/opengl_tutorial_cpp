//
// Created by chess on 2021/5/17.
//

#include "Director.h"

namespace sk {

void Director::Init(float width, float height) {

    ortho_projection = glm::ortho(0.0f, width, 0.0f, height, 0.0f, 1.0f);

}

glm::mat4 Director::GetOrthoProjection() {
    return ortho_projection;
}

}