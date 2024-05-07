//
// Created by KOSTJA on 04.05.2024.
//

#include "Figure.hpp"

void Figure::init() {
    GLuint VAO;
    GLuint VBO;
    for (int i = 0; i < 3; ++i) {

        glGenVertexArrays(1, &VAO);

        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.at(i).size() * sizeof(float), vertices.at(i).data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
        switch (i) {
            case 0:
                VAOs.emplace("centers", VAO);
                break;
            case 1:
                VAOs.emplace("edges", VAO);
                break;
            case 2:
                VAOs.emplace("corners", VAO);
                break;
            default:
                break;
        }
    }

    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, colliderVertices.size() * sizeof(float), colliderVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    VAOs.emplace("collider", VAO);
}

void Figure::updateVec(size_t n) {
    auto c1 = *corners.at(n).at(4);
    auto e1 = *edges.at(n).at(4);

    for (int i = 4; i > 0; --i) {
        *corners.at(n).at(i) = *corners.at(n).at(i - 1);
        *edges.at(n).at(i) = *edges.at(n).at(i - 1);
    }
    *corners.at(n).at(0) = c1;
    *edges.at(n).at(0) = e1;
}

void Figure::rotateSide(const vec3 sideVec, const float angle, const size_t n) {
    centers.at(n)->setModelMatrix(rotate(centers.at(n)->getModelMatrix(), radians(angle), vec3(0, 0, 1)));
    for (int i = 0; i < 5; ++i) {
        mat4 rot = rotate(mat4(1.0f), radians(angle), sideVec);
        edges.at(n).at(i)->setModelMatrix( rot * edges.at(n).at(i)->getModelMatrix());
        corners.at(n).at(i)->setModelMatrix( rot * corners.at(n).at(i)->getModelMatrix());
    }
}

Figure::Figure()  {
    edges.resize(12, std::vector<Piece*>(5, nullptr));
    corners.resize(12, std::vector<Piece*>(5, nullptr));
    centers.resize(12, nullptr);
    hitBoxes.resize(12);

    cens.resize(12);
    cens.at(0).rot(vec3(0,0,1), radians(180.0f));
    cens.at(0).mov(vec3(0,0,-4.55));
    for (int i = 1; i < 6; ++i) {
        cens.at(i).rot(vec3(1,0,0), radians(90.0f));
        cens.at(i).rot(vec3(0,1,0), radians(72.0f * (float)(i - 1)));
        cens.at(i).rot(vec3(1,0,0), radians(-26.565f));
        cens.at(i).mov(vec3(0,0,-4.55));
    }
    for (int i = 6; i < 11; ++i) {
        cens.at(i).rot(vec3(1,0,0), radians(90.0f));
        cens.at(i).rot(vec3(0,1,0), radians(36.0f));
        cens.at(i).rot(vec3(0,1,0), radians(72.0f * (float)(i - 6)));
        cens.at(i).rot(vec3(1,0,0), radians(26.565f));
        cens.at(i).mov(vec3(0,0,-4.55));
        cens.at(i).rot(vec3(0,0,1), radians(180.0f));
    }
    cens.at(11).rot(vec3(0,1,0), radians(180.0f));
    cens.at(11).mov(vec3(0,0,-4.55));

    hitBoxesBorder.resize(12);
    for (int i = 0; i < 12; ++i) {
        mat4 mod = rotate(cens.at(i).getModelMatrix(), radians(180.0f), vec3(0,0,1));
        hitBoxes.at(i).init(mod);
        hitBoxesBorder.at(i).setModelMatrix(mod);
        hitBoxes.at(i).setId(i);
    }

    edgs.resize(30);
    for (int i = 0; i < 15; i += 3) {
        for (int j = 0; j < 3; ++j) {
            edgs.at(i + j).rot(vec3(0,0,1), radians(72.0f * (float)(i / 3)));
            edgs.at(i + j).rot(vec3(0,0,1), radians(180.0f));
            edgs.at(i + j).rot(vec3(1,0,0), radians(-63.435f));
            edgs.at(i + j).mov(-vec3(0,0,4.55));
            edgs.at(i + j).rot(vec3(0,0,1), radians(-72.0f * (float)(j)));
            edgs.at(i + j).mov(vec3(0, 1.809, 0));
        }
    }
    for (int i = 15; i < 30; i += 3) {
        for (int j = 0; j < 3; ++j) {
            edgs.at(i + j).rot(vec3(0,0,1), radians(72.0f * (float)(i / 3)));
            edgs.at(i + j).rot(vec3(0,0,1), radians(180.0f));
            edgs.at(i + j).rot(vec3(1,0,0), radians(90.0f));
            edgs.at(i + j).rot(vec3(1,0,0), radians(26.565f));
            edgs.at(i + j).mov(-vec3(0,0,4.55));
            edgs.at(i + j).rot(vec3(0,0,1), radians(72.0f * (float)(j)));
            edgs.at(i + j).mov(vec3(0, 1.809, 0));
        }
    }

    cors.resize(20);
    for (int i = 0; i < 10; i += 2) {
        for (int j = 0; j < 2; ++j) {
            cors.at(i + j).rot(vec3(1,0,0), radians(90.0f));
            cors.at(i + j).rot(vec3(0,1,0), radians(36.0f * (float)(i)));
            cors.at(i + j).rot(vec3(1,0,0), radians(-26.565f));
            cors.at(i + j).mov(vec3(0,0,-4.55));
            cors.at(i + j).rot(vec3(0,0,1), radians(-36.0f));
            cors.at(i + j).rot(vec3(0,0,1), radians(-72.0f * (float)(j)));
            cors.at(i + j).mov(vec3(0.131,2.809,0));
        }
    }
    for (int i = 10; i < 20; i += 2) {
        for (int j = 0; j < 2; ++j) {
            cors.at(i + j).rot(vec3(1,0,0), radians(90.0f));
            cors.at(i + j).rot(vec3(0,1,0), radians(36.0f * (float)(i)));
            cors.at(i + j).rot(vec3(0,1,0), radians(36.0f));
            cors.at(i + j).rot(vec3(1,0,0), radians(26.565f));
            cors.at(i + j).mov(vec3(0,0,-4.55));
            cors.at(i + j).rot(vec3(0,0,1), radians(-72.0f * (float)(j)));
            cors.at(i + j).mov(vec3(0.131,2.809,0));
        }
    }
    int i = 0;
    int k1 = 2;
    for (auto& x : cors) {
        x.setColor(colors[k1 / 2]);
        ++i;
        ++k1;
        k1 %= 24;
    }
    i = 0;
    k1 = 4;
    int k2 = 5;
    for (auto& x : cors) {
        if (i < 10) x.setColor(colors[i % 2 == 0 ? ++k1 + 5 : k2++]);
        else x.setColor(colors[i % 2 == 0 ? 11 : ++k1 + 5]);
        k1 %= 5;
        k2 %= 6;
        if (k2 == 0) ++k2;
        ++i;
    }
    i = 0;
    k1 = 4, k2 = 1;
    for (auto& x : cors) {
        if (i < 10) x.setColor(colors[i % 2 != 0 ? 0 : ++k1]);
        else x.setColor(colors[i % 2 != 0 ? k2++ : ++k1 + 5]);
        ++i;
        k1 %= 5;
        k2 %= 6;
        if (k2 == 0) ++k2;
    }

    for (auto& x : cors) {
        x.setColor(vec3(0,0,0));
    }

    i = 0;
    for (auto& x : cens) {
        x.setColor(colors[i++]);
        x.setColor(vec3(0,0,0));
    }

    k1 = 1;
    for (i = 0; i < 15; i += 3) {
        edgs.at(i).setColor(colors[k1++]);
        edgs.at(i).setColor(colors[0]);
        k1 %= 6;
        if (k1 == 0) ++k1;
    }
    for (i = 1; i < 15; i += 3) {
        edgs.at(i).setColor(colors[k1]);
        edgs.at(i).setColor(colors[std::max((k1++ + 1) % 6, 1)]);
        k1 %= 6;
        if (k1 == 0) ++k1;
    }
    k1 = 1;
    for (i = 2; i < 15; i += 3) {
        edgs.at(i).setColor(colors[k1]);
        edgs.at(i).setColor(colors[k1++ + 5]);
        k1 %= 6;
        if (k1 == 0) ++k1;
    }
    k1 = 3;
    for (i = 15; i < 30; i += 3) {
        edgs.at(i).setColor(colors[k1++ + 5]);
        edgs.at(i).setColor(colors[11]);
        k1 %= 6;
        if (k1 == 0) ++k1;
    }
    k1 = 8;
    for (i = 16; i < 30; i += 3) {
        edgs.at(i).setColor(colors[k1]);
        ++k1;
        k1 %= 11;
        if (k1 == 0) k1 = 6;
        edgs.at(i).setColor(colors[k1]);
    }
    k1 = 8;
    for (i = 17; i < 30; i += 3) {
        edgs.at(i).setColor(colors[k1]);
        ++k1;
        k1 %= 11;
        if (k1 == 0) k1 = 6;
        edgs.at(i).setColor(colors[k1 - 5]);
    }

    for (auto& x : edgs) {
        x.setColor(vec3(0,0,0));
    }

    for (i = 0; i < 12; ++i) {
        for (int j = 0; j < pointers.at(i).size() / 2; ++j) {
            edges.at(i).at(j) = &edgs.at(pointers.at(i).at(j));
            corners.at(i).at(j) = &cors.at(pointers.at(i).at(j + 5));
        }
    }
    for (i = 0; i < 12; ++i) {
        centers.at(i) = &cens.at(i);
    }

}

void Figure::enableVAO(std::string s) {
    currentVAO = s;
    glBindVertexArray(VAOs.at(s));
}

void Figure::disableVAO() {
    glBindVertexArray(0);
}

Collider Figure::getHitbox(size_t n) {
    return hitBoxes.at(n);
}

mat4 Figure::getModel(size_t n) {
    if (currentVAO == "centers") {
        return cens.at(n).getModelMatrix();
    }
    if (currentVAO == "edges") {
        return edgs.at(n).getModelMatrix();
    }
    if (currentVAO == "corners") {
        return cors.at(n).getModelMatrix();
    }
    if (currentVAO == "collider") {
        return hitBoxesBorder.at(n).getModelMatrix();
    }
}

vec3 Figure::getNormalVector(size_t n) {
    return sideVecs.at(n);
}

vec3 Figure::getColor(size_t n, size_t i) {

    if (currentVAO == "centers") {
        return cens.at(n).getColor(i);
    }
    if (currentVAO == "edges") {
        return edgs.at(n).getColor(i);
    }
    if (currentVAO == "corners") {
        return cors.at(n).getColor(i);
    }
    if (currentVAO == "collider") {
        return hitBoxesBorder.at(n).getColor(i);
    }
}
