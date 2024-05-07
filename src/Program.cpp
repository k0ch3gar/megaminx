//
// Created by KOSTJA on 03.05.2024.
//

#include "Program.hpp"

bool readFile(const std::string& path, std::string& s) {
    std::ifstream shaderFile;

    shaderFile.exceptions(std::ifstream::badbit);
    try {
        shaderFile.open(path);
        std::stringstream shaderStream;

        shaderStream << shaderFile.rdbuf();

        shaderFile.close();

        s = shaderStream.str();
    }
    catch(std::ifstream::failure& e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        return false;
    }
    return true;
}


bool Program::init() {
    m_progId = glCreateProgram();

    if (m_progId != 0)return true;

    std::cerr << "[ERROR] Couldn't create program\n";
    return false;
}

void Program::enable() {
    glUseProgram(m_progId);
}

GLuint Program::getProgram() const {
    return m_progId;
}

bool Program::addShader(GLenum shaderType, const char *path) {
    std::string s;
    if (!readFile(path, s)) {
        std::cerr << "[ERROR] Couldn't read file\n";
        return false;
    }

    GLuint shaderObj = glCreateShader(shaderType);
    if (shaderObj == 0) {
        std::cerr << "[ERROR] Couldn't create shader\n";
        return false;
    }

    m_shaderObjList.emplace_back(shaderObj);
    const GLchar* p;
    p = s.c_str();
    GLint len = (GLint)s.size();

    glShaderSource(shaderObj, 1, &p, &len);

    glCompileShader(shaderObj);

    GLint success;
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);

    if (success == 0) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shaderObj, 1024, NULL, infoLog);
        std::cerr << "[ERROR] Couldn't compile shader: " << infoLog;
        return false;
    }

    glAttachShader(m_progId, shaderObj);

    return true;
}

bool Program::finalize() {
    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(m_progId);

    glGetProgramiv(m_progId, GL_LINK_STATUS, &Success);
    if (Success == 0) {
        glGetProgramInfoLog(m_progId, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        return false;
    }

    glValidateProgram(m_progId);
    glGetProgramiv(m_progId, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(m_progId, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        return false;
    }

    for (auto& it : m_shaderObjList) {
        glDeleteShader(it);
    }

    m_shaderObjList.clear();

    return true;
}

GLint Program::getUniformLocation(const char* s) {
    GLint loc = glGetUniformLocation(m_progId, s);
    return loc;
}

