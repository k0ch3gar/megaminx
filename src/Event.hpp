//
// Created by KOSTJA on 16.04.2024.
//

#ifndef MEGAMINX_EVENT_HPP
#define MEGAMINX_EVENT_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#define MOUSE_INDEX 1024

void keyboardAction(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouseAction(GLFWwindow* window, int key, int action, int mode);
void windowResizeCallback(GLFWwindow* window, int width, int height);
void cursorCallBack(GLFWwindow* window, double x, double y);

class Event {
    std::unordered_map<size_t, bool> keys;
    std::unordered_map<size_t, size_t> frames;
    std::pair<double, double> mousePos;
    size_t currentFrame{};
    double dX{};
    double dY{};
public:
    int w{}, h{};

    Event() = default;
    ~Event() = default;

    void setWH(int w_, int h_);

    void setMousePos(double x, double y);

    std::pair<double, double> getMousePos();

    std::pair<int, int> getWH();

    void init(GLFWwindow* window);

    void setKey(const size_t key, const bool data);

    void updateFrame(const size_t key);

    bool isMouseBPressed(size_t key);

    bool isMouseBJustPressed(size_t key);

    bool isKeyPressed(size_t key);

    bool isKeyJustPressed(size_t key);

    void pullEvents();

};






#endif //MEGAMINX_EVENT_HPP
