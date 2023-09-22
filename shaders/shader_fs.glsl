#version 410 

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D our_texture; // Texture uniform

void main() {
    FragColor = texture(our_texture, TexCoord) * vec4(1.0f);
}