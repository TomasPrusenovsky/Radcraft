#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

uniform mat4 u_proj;
uniform mat4 u_view;
uniform mat4 u_model;

out vec2 UV;

void main() {
    UV = aUV;
    gl_Position = u_proj * u_view * u_model * vec4(aPos, 1.0);
}