#version 460 core

in vec2 UV;

out vec4 FragColor;

uniform sampler2D u_tex;

void main() {
    FragColor = vec4(1.0, 0.0, 1.0, 1.0);
    FragColor = texture(u_tex, UV);
}