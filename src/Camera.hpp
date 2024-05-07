//
// Created by KOSTJA on 18.04.2024.
//

#ifndef MEGAMINX_CAMERA_HPP
#define MEGAMINX_CAMERA_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL

using namespace glm;

class Camera {
    float pitch = 0;
    float yaw = 3.14;
    float fov{};
    float distance = 5;

    vec3 object{0.0f,0.0f,0.0f};
    vec3 position{0.0f,0.0f,0.0f};
    vec3 up{0.0f,1.0f,0.0f};

    mat4 view = mat4(1.0f);
public:
    Camera() = default;
    Camera(vec3 object, float fov, vec3 position);
    void setPitch(float angle);
    void setYaw(float angle);
    void updateVectors();

    mat4 getView();
    vec3 getPosition();
    float getFov();
};

#endif //MEGAMINX_CAMERA_HPP
