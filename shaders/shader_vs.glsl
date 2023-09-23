#version 410 

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 mvp;
uniform float rotation; // New uniform variable for rotation

void main() {
    // Apply rotation to the vertex position
    mat2 rotation_matrix = mat2(cos(rotation), -sin(rotation), sin(rotation), cos(rotation));
    vec2 rotated_position = rotation_matrix * position.xy;

    gl_Position = mvp * vec4(rotated_position, 1.0, 1.0);
    TexCoord = texCoord;
}
