cmake_minimum_required(VERSION 3.27)
project(megaminx)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)

add_executable(megaminx main.cpp
        src/Window.hpp
        src/Event.hpp
        src/Shader.hpp
        src/Figure.hpp
        src/Camera.hpp
        src/Camera.cpp
        src/Event.cpp
        src/Window.cpp
        src/Shader.cpp
        src/Program.cpp
        src/Program.hpp
        src/Figure.cpp
        src/Vertices.cpp
        src/PickingShader.hpp
        src/PickingShader.cpp
        src/Collider.cpp
        src/Collider.hpp
)

target_link_libraries(${PROJECT_NAME}
        glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES}
        libglew_static
        glm::glm
)
target_include_directories(${PROJECT_NAME} PUBLIC ${GLEW_INCLUDES})