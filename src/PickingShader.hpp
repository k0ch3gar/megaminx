//
// Created by KOSTJA on 03.05.2024.
//

#ifndef MEGAMINX_PICKINGSHADER_HPP
#define MEGAMINX_PICKINGSHADER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <utility>

#include "Program.hpp"

using namespace glm;

class PickingTechnique : public Program {
public:

    PickingTechnique() = default;

    bool init();

    void setModel(const mat4& model) const;
    void setColor(const vec3& color) const;
    void drawTriangle(int shift, int amount);
    void drawLine(int shift, int amount);

private:
    GLint m_modelLocation;
    GLint m_colorLocation;
};

#endif //MEGAMINX_PICKINGSHADER_HPP
