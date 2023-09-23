#version 410

layout (location = 0) in vec3 position;
layout (location = 2) in vec3 color; // Color attribute
layout (location = 1) in vec2 texCoord;

out vec2 TexCoord;
out vec3 FragColor; // Output color to fragment shader

uniform mat4 mvp;

void main() {
    gl_Position = mvp * vec4(position, 1.0);
    TexCoord = texCoord;
    
    // Pass the color attribute to the fragment shader
    FragColor = color;
}
