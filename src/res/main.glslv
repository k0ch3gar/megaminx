#version 330 core

layout (location = 0) in vec3 v_position;
out vec4 a_color;

uniform mat4 model;
uniform vec3 in_color;

void main() {
	a_color = vec4(in_color, 1.0f);
	gl_Position = model * vec4(v_position, 1.0f);
}