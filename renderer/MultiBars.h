//
// Created by chess on 2021/5/18.
//

#ifndef OPENGL_TUTORIAL_MULTIBARS_H
#define OPENGL_TUTORIAL_MULTIBARS_H

#include "IRenderer.h"

namespace sk {

class MultiBars : public IRenderer {
public:

    MultiBars(const std::string& vs_path, const std::string& fs_path);
    ~MultiBars();

    void Render(float delta) override;


private:


};

}

#endif //OPENGL_TUTORIAL_MULTIBARS_H
