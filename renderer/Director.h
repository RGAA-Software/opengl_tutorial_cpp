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

private:
    glm::mat4           ortho_projection;

};

}

#endif //OPENGL_TUTORIAL_DIRECTOR_H
