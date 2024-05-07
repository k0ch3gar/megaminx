//
// Created by KOSTJA on 05.05.2024.
//

#include "Collider.hpp"

bool Collider::isCollide(const vec3 &dot) const {
    for (int i = 1; i < colliderVec4.size(); i += 2) {
        vec3 vect = colliderVec4.at(i);
        vec3 tmp = dot - colliderVec4.at(i - 1);
        vec3 tmp2 = cross(vect, tmp);
        tmp2 = normalize(tmp2);
        //std::cout << ".... " << tmp2.x << ' ' << tmp2.y << ' ' << tmp.z << '\n';
        if (angle(tmp2, normal) > radians(10.0f)) return false;
    }
    return true;
}

void Collider::init(const mat4 &model) {
    for (int i = 0; i < colliderVec4.size(); ++i) {
        colliderVec4.at(i) = model * vec4(colliderVec4.at(i), (i + 1) % 2);
    }
    normal = normalize(cross(colliderVec4.at(1), colliderVec4.at(3)));
}

void Collider::init() {
    for (int i = 0; i < colliderVec4.size(); i += 2) {
        colliderVec4.at(i).z = -4.55;
    }
    std::cout << colliderVec4.at(1).x << ' ' << colliderVec4.at(1).y << ' ' << colliderVec4.at(1).z << '\n';
    normal = normalize(cross(colliderVec4.at(1), colliderVec4.at(3)));
    std::cout << normal.x << ' ' << normal.y << ' ' << normal.z << '\n';
}

vec3 Collider::getNormal() {
    return normal;
}

size_t Collider::getId() const {
    return id;
}

float Collider::getDistance(const vec3 &origin, const vec3& ray) const {

    float t = -(dot(normal, origin) - 4.55f) / (dot(normal, ray));

    if (t < 0) return -1;

    return t;
}

void Collider::setId(size_t newId) {
    this->id = newId;
}
