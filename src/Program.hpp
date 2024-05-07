//
// Created by KOSTJA on 03.05.2024.
//

#ifndef MEGAMINX_PROGRAM_HPP
#define MEGAMINX_PROGRAM_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <utility>
#include <list>

class Program {
public:

    Program() = default;

    virtual bool init();

    GLuint getProgram() const;

    void enable();

protected:

    bool addShader(GLenum shaderType, const char* path);
    bool finalize();

    GLint getUniformLocation(const char* s);

private:
    GLuint m_progId;
    std::list<GLuint> m_shaderObjList;
};


#endif //MEGAMINX_PROGRAM_HPP
