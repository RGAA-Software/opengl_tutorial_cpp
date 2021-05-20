//
// Created by chess on 2021/5/20.
//

#ifndef OPENGL_TUTORIAL_INPUTPROCESSOR_H
#define OPENGL_TUTORIAL_INPUTPROCESSOR_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace sk {

class InputProcessor {
public:

    static InputProcessor* Instance() {
        static InputProcessor instance;
        return &instance;
    }

    void ProcessEvent(GLFWwindow* window, float delta);
    void ProcessCursor(double x, double y);

private:

    float last_x = 0;
    float last_y = 0;
    bool  first_enter = true;

    float pitch = 0;
    float yaw = 270;
};

}

#endif //OPENGL_TUTORIAL_INPUTPROCESSOR_H
