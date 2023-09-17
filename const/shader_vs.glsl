#version 400

layout(location = 0) in vec3 vp;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

void main() {
    
    mat4 MVP = projectionMatrix * modelMatrix;

    gl_Position = MVP * vec4(vp, 1.0);
}