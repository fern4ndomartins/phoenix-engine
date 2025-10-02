#version 330 core
out vec4 LineColor;
uniform vec3 color;   

void main() {
    LineColor = vec4(color, 1.0); // black
}