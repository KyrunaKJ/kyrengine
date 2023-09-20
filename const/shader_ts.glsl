#version 400
// Input from the vertex shader
in vec2 FragTexCoord;

// Texture unit
uniform sampler2D smile_text;

// Output color
out vec4 frag_color;

void main() {
    // Sample the texture using the provided texture coordinates
    frag_color = texture(smile_text, FragTexCoord);
}