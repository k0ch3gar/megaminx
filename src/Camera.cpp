//
// Created by KOSTJA on 03.05.2024.
//


#include "Camera.hpp"

float Camera::getFov() {
    return fov;
}

mat4 Camera::getView() {
    return view;
}

void Camera::updateVectors() {
    position.x = sin(yaw) * cos(pitch) * distance;
    position.y = sin(pitch) * distance;
    position.z = cos(yaw) * cos(pitch) * distance;
    up.y = cos(pitch);
    view = lookAt(position, object, up);
}

void Camera::setYaw(float angle)  {
    yaw += angle * (distance / 2.0f);
    updateVectors();
}

void Camera::setPitch(float angle) {
    pitch += angle * (distance / 2.0f);
    updateVectors();
}

Camera::Camera(vec3 object, float fov, vec3 position) : object(object), fov(fov), position(position) {
    distance = glm::distance(position, object);
    view = lookAt(position, object, up);
}

vec3 Camera::getPosition() {
    return position;
}
