//
// Created by KOSTJA on 17.04.2024.
//

#ifndef MEGAMINX_SHADER_HPP
#define MEGAMINX_SHADER_HPP

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

//#include "PickingShader.hpp"
#include "Program.hpp"

using namespace glm;


class Shader : public Program {
    GLint m_modelLoc;
    GLint m_colorLoc;
public:

    Shader() = default;
    ~Shader();

    void uniformMatrix(const glm::mat4& matrix) const;
    virtual bool init();
    void uniformVector(const glm::vec3& vector) const;
    void drawTriangles(int shift, int size) const;
    void drawLines(int shift, int size) const;
};



#endif //MEGAMINX_SHADER_HPP
