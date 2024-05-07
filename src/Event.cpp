//
// Created by KOSTJA on 03.05.2024.
//

#include "Event.hpp"

void keyboardAction(GLFWwindow* window, int key, int scancode, int action, int mode) {
    auto win = (Event*)glfwGetWindowUserPointer(window);
    if (action == GLFW_PRESS) {
        win->setKey(key, true);
        win->updateFrame(key);
        return;
    }
    if (action == GLFW_RELEASE) {
        win->setKey(key, false);
        win->updateFrame(key);
        return;
    }
}

void windowResizeCallback(GLFWwindow* window, int width, int height) {
    auto win = (Event*)glfwGetWindowUserPointer(window);
    win->w = width;
    win->h = height;
    glViewport(0, 0, width, height);
}

void mouseAction(GLFWwindow* window, int key, int action, int mode) {
    auto win = (Event*)glfwGetWindowUserPointer(window);
    if (action == GLFW_PRESS) {
        win->setKey(MOUSE_INDEX + key, true);
        win->updateFrame(MOUSE_INDEX + key);
        return;
    }
    if (action == GLFW_RELEASE) {
        win->setKey(MOUSE_INDEX + key, false);
        win->updateFrame(MOUSE_INDEX + key);
        return;
    }
}

void cursorCallBack(GLFWwindow *window, double x, double y) {
    auto win = (Event*)glfwGetWindowUserPointer(window);
    win->setMousePos(x, y);
}

void Event::setWH(const int w_, const int h_) {
    this->w = w_;
    this->h = h_;
}

std::pair<int, int> Event::getWH() {
    return {w, h};
}

void Event::init(GLFWwindow *window) {
    w = 1280;
    h = 720;
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, keyboardAction);
    glfwSetMouseButtonCallback(window, mouseAction);
    glfwSetWindowSizeCallback(window, windowResizeCallback);
    glfwSetCursorPosCallback(window, cursorCallBack);
}

void Event::setKey(const size_t key, const bool data) {
    keys.emplace(key, data);
    keys.at(key) = data;
}

void Event::updateFrame(const size_t key) {
    frames.emplace(key, currentFrame);
    frames.at(key) = currentFrame;
}

bool Event::isMouseBPressed(size_t key) {
    return keys.contains(MOUSE_INDEX + key) && keys.at(MOUSE_INDEX + key);
}

bool Event::isMouseBJustPressed(size_t key) {
    return keys.contains(MOUSE_INDEX + key) && keys.at(MOUSE_INDEX + key) && currentFrame == frames.at(MOUSE_INDEX + key);
}

bool Event::isKeyPressed(size_t key) {
    return keys.contains(key) && keys.at(key);
}

bool Event::isKeyJustPressed(size_t key) {
    return keys.contains(key) && keys.at( key) && currentFrame == frames.at(key);
}

void Event::pullEvents() {
    ++currentFrame;
    dX = 0;
    dY = 0;
    glfwPollEvents();
}

void Event::setMousePos(double x, double y) {
    mousePos = std::make_pair(x, y);
}

std::pair<double, double> Event::getMousePos() {
    return mousePos;
}
