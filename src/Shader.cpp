//
// Created by KOSTJA on 03.05.2024.
//

#include "Shader.hpp"



void Shader::drawTriangles(int shift, int size) const  {
    glDrawArrays(GL_TRIANGLES, shift, size);
}

void Shader::drawLines(int shift, int size) const {
    glDrawArrays(GL_LINE, shift, size);
}


void Shader::uniformMatrix(const glm::mat4& matrix) const {
    glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, value_ptr(matrix));
}

void Shader::uniformVector(const vec3 &vector) const {
    glUniform3fv(m_colorLoc, 1, glm::value_ptr(vector));
}

Shader::~Shader() {
    glDeleteProgram(getProgram());
}

bool Shader::init() {

    if (!Program::init()) {
        return false;
    }

    if (!Program::addShader(GL_VERTEX_SHADER, "../src/res/main.glslv")) {
        return false;
    }

    if (!Program::addShader(GL_FRAGMENT_SHADER, "../src/res/main.glslf")) {
        return false;
    }

    if (!finalize()) {
        return false;
    }

    m_modelLoc = Program::getUniformLocation("model");
    m_colorLoc = Program::getUniformLocation("in_color");

    return true;
}
