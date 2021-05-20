//
// Created by chess on 2021/5/17.
//

#ifndef OPENGL_TUTORIAL_DIRECTOR_H
#define OPENGL_TUTORIAL_DIRECTOR_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace sk {

class Director {
public:

    static Director* Instance() {
        static Director instance;
        return &instance;
    }

    void Init(float width, float height);

    glm::mat4 GetOrthoProjection();
    glm::mat4 GetPerspectiveProjection();
    glm::mat4 GetCameraLookAt();

    glm::vec3 GetCameraPosition();
    void UpdateCameraPosition(const glm::vec3& pos);

    glm::vec3 GetCameraFront();
    void UpdateCameraFront(const glm::vec3& front);

    glm::vec3 GetCameraUp();

private:
    glm::mat4           ortho_projection;

    glm::mat4           perspective_projection;
    glm::mat4           camera_look_at;
    glm::vec3           camera_pos;
    glm::vec3           camera_front;
    glm::vec3           camera_up;

};

}

#endif //OPENGL_TUTORIAL_DIRECTOR_H
