//
// Created by KOSTJA on 05.05.2024.
//

#ifndef MEGAMINX_COLLIDER_HPP
#define MEGAMINX_COLLIDER_HPP


#define GLM_ENABLE_EXPERIMENTAL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <iostream>


using namespace glm;



class Collider {
public:

    Collider() = default;
    void init(const mat4& model);
    void init();

    ~Collider() = default;

    vec3 getNormal();

    bool isCollide(const vec3& dot) const;

    size_t getId() const;
    void setId(size_t newId);

    float getDistance(const vec3& origin, const vec3& ray) const;

private:
    double epsilon = 1.0e-7;
    size_t id;
    vec3 normal;
    std::vector<vec3> bounderies;
    std::vector<vec3> colliderVec4 = {
            vec3(0, -3.5, 0),
            vec3(-3.3285, 2.4185, 0),

            vec3(-3.3285, -1.0815, 0),
            vec3(1.274, 3.913, 0),

            vec3(-2.0545, 2.8315, 0),
            vec3(4.109, 0, 0),

            vec3(2.0545, 2.8315, 0),
            vec3(1.274, -3.913, 0),

            vec3(3.3285, -1.0815, 0),
            vec3(-3.3285, -2.4185, 0),
    };
};


#endif //MEGAMINX_COLLIDER_HPP
