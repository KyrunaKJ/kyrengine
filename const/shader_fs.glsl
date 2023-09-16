#version 400
out vec4 frag_color;
float red = 173 / 255;
float green = 255 / 255;
float blue = 47 / 255;
void main() {
    // frag_color = vec4(0.5, 0.0, 0.5, 1.0); // first magenta
    // frag_color = vec4(0.5, 0.5, 0.5, 1.0); // second gray
    // frag_color = vec4(0.5, 0.0, 0.0, 1.0); // third red
    // frag_color = vec4(0.0, 0.5, 0.0, 1.0); // fourth green
    // frag_color = vec4(0.0, 0.0, 0.5, 1.0); // fifth blue
    frag_color = vec4(red, green, blue, 1.0); // custom
};