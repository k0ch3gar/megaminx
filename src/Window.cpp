//
// Created by KOSTJA on 03.05.2024.
//

#include "Window.hpp"

Window::Window(int width, int height, const char *title) : width(width), height(height), title(title) {
        glfwInit();
        glPointSize(1.0);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        window = glfwCreateWindow(width, height, "title", nullptr, nullptr);
        if (window == nullptr) {
            std::cerr << "Couldn't create window!\n";
            glfwTerminate();
            return;
        }

        events = Event();
        events.init(window);
}

Window::~Window() {
    glfwTerminate();
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

void Window::show() {
    glViewport(0, 0, width, height);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialized glew!\n";
        glfwTerminate();
        return;
    }
}

void Window::setClosed(const bool data) {
    glfwSetWindowShouldClose(window, data);
}

bool Window::isClosed() {
    return glfwWindowShouldClose(window);
}

void Window::updateWH(std::pair<int, int> WH) {
    width = WH.first;
    height = WH.second;
}

float Window::getAspect() {
    updateWH(std::pair<int, int>(events.w, events.h));
    return (float)width / (float)height;
}
