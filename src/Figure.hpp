//
// Created by KOSTJA on 17.04.2024.
//

#ifndef MEGAMINX_FIGURE_HPP
#define MEGAMINX_FIGURE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <iostream>
#include <vector>

#define GLM_ENABLE_EXPERIMENTAL

#include "Vertices.cpp"
#include "Collider.hpp"


using namespace glm;

class Piece {
    mat4 model{};
    std::vector<vec3> color;
public:
    Piece() {
        model = mat4(1.0f);
    }

    ~Piece() = default;

    void setColor(const vec3& c) {
        color.emplace_back(c);
    }

    vec3 getColor(size_t n) {
        return color.at(n);
    }

    void rot(const vec3 axis, const float angle) {
        model = rotate(model, angle, axis);
    }

    void mov(const vec3 offset) {
        model = translate(model, offset);
    }

    mat4 getModelMatrix() {
        return model;
    }

    void setModelMatrix(const mat4& x) {
        model = x;
    }

};

class Figure {
    vec3 colors[12] = {
            vec3(1,1,1),
            vec3(1,0,0),
            vec3(0,1,0),
            vec3(0,0,1),
            vec3(0,0.5,0.5),
            vec3(0.5,0,0.5),
            vec3(1,0.91,0.43),
            vec3(1,0.43,0),
            vec3(1,0.45,0.76),
            vec3(0.05,0.48,0.12),
            vec3(0.7,0.72,0.74),
            vec3(0.44,0.2,0.1),
    };

    std::vector<std::vector<size_t>> pointers = {
            {0, 3, 6, 9, 12, 1, 3, 5, 7, 9},
            {2, 1, 0, 13, 23, 11, 2, 3, 1, 0},
            {26, 5, 4, 3, 1, 3, 2, 13, 4, 5},
            {29, 8, 7, 6, 4, 6, 7, 5, 4, 15},
            {11, 10, 9, 7, 17, 8, 9, 7, 6, 17},
            {14, 13, 12, 10, 20, 0, 1, 9, 8, 19},
            {24, 25, 26, 2, 22, 11, 10, 12, 13, 2},
            {25, 27, 28, 29, 5, 13, 12, 14, 15, 4},
            {28, 15, 16, 17, 8, 15, 14, 16, 17, 6},
            {16, 18, 19, 20, 11, 17, 16, 18, 19, 8},
            {19, 21, 22, 23, 14, 19, 18, 10, 11, 0},
            {27, 24, 21, 18, 15, 18, 16, 14, 12, 10}
    };



    std::unordered_map<std::string, GLuint> VAOs;
    std::vector<vec3> sideVecs = {
            vec3(0, 0, 1),
            vec3(0, -0.894428, 0.447213),
            vec3(0.850651, -0.276393, 0.447213),
            vec3(0.525731, 0.723607, 0.447213),
            vec3(-0.525731, 0.723607, 0.447213),
            vec3(-0.850651, -0.276393, 0.447213),
            vec3(0.525731, -0.723607, -0.447213),
            vec3(0.850651, 0.276393, -0.447213),
            vec3(-7.81933e-08, 0.894428, -0.447213),
            vec3(-0.850651, 0.276393, -0.447213),
            vec3(-0.525731, -0.723607, -0.447213),
            vec3(0, 0, -1)
    };
    std::vector<std::vector<Piece*>> edges;
    std::vector<std::vector<Piece*>> corners;
    std::vector<Piece*> centers;
    std::vector<Piece> cors, cens, edgs;
    std::vector<Piece> hitBoxesBorder;
    std::vector<Collider> hitBoxes;
    std::string currentVAO;
public:
    Figure();

    void rotateSide(const vec3 sideVec, const float angle, const size_t n);

    void updateVec(size_t n);

    Collider getHitbox(size_t n);
    mat4 getModel(size_t n);
    vec3 getColor(size_t n, size_t i);
    vec3 getNormalVector(size_t n);

    void enableVAO(std::string s);
    void disableVAO();

    void init();
};

#endif //MEGAMINX_FIGURE_HPP
