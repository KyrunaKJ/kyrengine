#version 410
out vec4 FragColor;

void main() {
    // Calculate a color based on the x-coordinate of the fragment
    float x = gl_FragCoord.x / 400.0; // Adjust 800.0 to match your screen width
    vec3 color = vec3(x, 0.0, 1.0 - x); // Varies from red to blue as x changes

    FragColor = vec4(color, 1.0);
}
