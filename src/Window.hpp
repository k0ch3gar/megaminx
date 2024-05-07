//
// Created by KOSTJA on 16.04.2024.
//

#ifndef MEGAMINX_WINDOW_HPP
#define MEGAMINX_WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <iostream>

#include "Event.hpp"

#define GLM_ENABLE_EXPERIMENTAL

using namespace glm;

class Window {
    int width;
    int height;
    const char* title;
    GLFWwindow* window;

    mat4 perspective = mat4(1.0f);
public:
    Event events;

    Window(int width, int height, const char* title);

    ~Window();

    void swapBuffers();

    void show();

    void setClosed(const bool data);

    bool isClosed();

    void updateWH(std::pair<int, int> WH);

    float getAspect();


};

#endif //MEGAMINX_WINDOW_HPP
