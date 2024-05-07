#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "src/Window.hpp"
#include "src/Shader.hpp"
#include "src/Figure.hpp"
#include "src/Camera.hpp"
#include "src/PickingShader.hpp"
#include "src/Collider.hpp"

#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL



int width = 1280;
int height = 720;


int main() {

    Window window(width, height, "t1");
    window.show();
    glEnable(GL_DEPTH_TEST);

    auto* mainShader = new Shader();
    mainShader->init();
    Camera cam(vec3(0,0,0), 70.0f, vec3(0,0,-15));
    glClearColor(0.3,0.3,0.3,1);

    PickingTechnique m_pc;

    Figure meg;
    meg.init();
    m_pc.init();
    Collider col;
    col.init();

    int u = 0, t = 0;
    int sideIndex = 0;
    vec4 sideVec(0,0,1, 1);
    mat4 rot(1.0f);
    while (!window.isClosed()) {
        window.events.pullEvents();
        if (window.events.isKeyJustPressed(GLFW_KEY_ESCAPE)) {
            window.setClosed(true);
        }

        if (!u) sideVec = vec4(0,0,1,1);

        if (window.events.isKeyPressed(GLFW_KEY_A)) {
            cam.setYaw(-0.001f);
        }
        if (window.events.isKeyPressed(GLFW_KEY_W)) {
            cam.setPitch(0.001f);
        }
        if (window.events.isKeyPressed(GLFW_KEY_D)) {
            cam.setYaw(0.001f);
        }
        if (window.events.isKeyPressed(GLFW_KEY_S)) {
            cam.setPitch(-0.001f);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mat4 model;
        mat4 proj = perspective(cam.getFov(), window.getAspect(), 1.0f, 100.0f);
        if (window.events.isMouseBPressed(GLFW_MOUSE_BUTTON_LEFT)) {
            vec3 mousePos = vec3((-1.0f * (float)window.getAspect() * ((float)window.events.getMousePos().first - ((float)window.events.w / 2.0f)) / ((float)window.events.w / 2.0f)), ((float)(window.events.h - window.events.getMousePos().second - 1) - ((float)window.events.h / 2.0f)) / ((float)window.events.h / 2.0f), 0);
            vec3 pos = vec3(-cam.getPosition());
            pos = normalize(pos);
            vec3 dev = cross(vec3(mousePos), pos);
            pos = pos * 7.21f;
            dev = cross(pos, dev);
            vec3 absolute = vec3(-cam.getPosition()) + dev;
            absolute = normalize(absolute);
            Collider minCorrect;
            float t = 1000;
            size_t hitId = -1;
            for (int i = 0; i < 12; ++i) {
                float temp = meg.getHitbox(i).getDistance(cam.getPosition(), absolute);
                if (temp < 0) continue;
                if (meg.getHitbox(i).isCollide(cam.getPosition() + absolute * temp) && temp < t) {
                    t = temp;
                    hitId = meg.getHitbox(i).getId();
                }
            }
            if (hitId != -1 && u == 0 && window.events.isMouseBJustPressed(GLFW_MOUSE_BUTTON_LEFT)) {
                u = 72 * 2;
                sideVec = vec4(meg.getNormalVector(hitId), 0);
                sideIndex = hitId;
            }
            if (hitId != -1) {
                glEnable(GL_LINE_SMOOTH);
                glLineWidth(5.0f);
                m_pc.enable();
                meg.enableVAO("collider");
                m_pc.setModel(proj * cam.getView() * meg.getModel(hitId));
                m_pc.setColor(vec3(0,0,1));
                m_pc.drawLine(0, 30);
                glDisable(GL_LINE_SMOOTH);
            }
        }

        if (window.events.isKeyJustPressed(GLFW_KEY_V)) {
            if (u == 0) {
                u = 72 * 2;
                sideIndex = 0;
            }
        }
        if (window.events.isKeyJustPressed(GLFW_KEY_G)) {
            if (u == 0) {
                u = 72 * 2;
                rot = rotate(mat4(1.0f), radians(116.565f), vec3(1,0,0));
                sideVec = rot * sideVec;
                rot = rotate(mat4(1.0f), radians(324.0f), vec3(0,0,1));
                sideVec = rot * sideVec;
                std::cout << sideVec.x << ' ' << sideVec.y << ' ' << sideVec.z << '\n';
                sideIndex = 10;
            }
        }
        if (window.events.isKeyJustPressed(GLFW_KEY_R)) {
            if (u == 0) {
                u = 72 * 2;
                rot = rotate(mat4(1.0f), radians(63.435f), vec3(1,0,0));
                sideVec = rot * sideVec;
                sideIndex = 1;
            }
        }

        if (u != 0) {
            u--;
            meg.rotateSide(sideVec, 0.5f, sideIndex);
            if (u == 0) meg.updateVec(sideIndex);
        }


        mainShader->enable();
        meg.enableVAO("corners");
        for (int i = 0; i < 20; ++i) {
            model = proj * cam.getView() * meg.getModel(i);
            mainShader->uniformMatrix(model);
            for (int j = 0; j < 3; ++j) {
                mainShader->uniformVector(meg.getColor(i, j));
                mainShader->drawTriangles(j * 6, 6);
            }
            mainShader->uniformVector(vec3(0, 0, 0));
            mainShader->drawTriangles(18, 12);
        }
        meg.enableVAO("edges");
        for (int i = 0; i < 30; ++i) {
            model = proj * cam.getView() * meg.getModel(i);
            mainShader->uniformMatrix(model);
            for (int j = 0; j < 2; ++j) {
                mainShader->uniformVector(meg.getColor(i, j));
                mainShader->drawTriangles(j * 3, 3);
            }
            mainShader->uniformVector(vec3(0, 0, 0));
            mainShader->drawTriangles(6, 12);
        }
        meg.enableVAO("centers");
        for (int i = 0; i < 12; ++i) {
            model = proj * cam.getView() * meg.getModel(i);
            mainShader->uniformMatrix(model);
            mainShader->uniformVector(meg.getColor(i, 0));
            mainShader->drawTriangles(0, 9);
            mainShader->uniformVector(vec3(0, 0, 0));
            mainShader->drawTriangles(9, 15);
        }
        meg.disableVAO();
        window.swapBuffers();
    }
    return 0;
}