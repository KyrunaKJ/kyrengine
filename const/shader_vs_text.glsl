#version 400

layout(location = 0) in vec3 vp;
layout (location = 1) in vec3 aColor;
layout(location = 2) in vec2 TexCoord; // Texture coordinates

uniform mat4 projectionMatrixText;
uniform mat4 modelMatrixText;

out vec2 FragTexCoord; // Pass texture coordinates to the fragment shader

void main() {
    mat4 MVP = projectionMatrixText * modelMatrixText;
    gl_Position = MVP * vec4(vp, 1.0);
    
    FragTexCoord = TexCoord; // Pass texture coordinates to the fragment shader
}
