//
// Created by KOSTJA on 04.05.2024.
//

#include "PickingShader.hpp"


bool PickingTechnique::init() {
    if (!Program::init()) {
        return false;
    }

    if (!addShader(GL_VERTEX_SHADER, "../src/res/picking.vs")) {
        return false;
    }

    if (!addShader(GL_FRAGMENT_SHADER, "../src/res/picking.fs")) {
        return false;
    }

    if (!finalize()) {
        return false;
    }

    m_modelLocation = getUniformLocation("model");
    m_colorLocation = getUniformLocation("in_color");
    return true;
}

void PickingTechnique::setModel(const mat4 &model) const {
    glUniformMatrix4fv(m_modelLocation, 1, GL_FALSE, value_ptr(model));
}

void PickingTechnique::setColor(const vec3 &color) const {
    glUniform3fv(m_colorLocation, 1, value_ptr(color));
}

void PickingTechnique::drawLine(int shift, int amount) {
    glDrawArrays(GL_LINES, shift, amount);
}

void PickingTechnique::drawTriangle(int shift, int amount) {
    glDrawArrays(GL_TRIANGLES, shift, amount);
}