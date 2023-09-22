#version 410
out vec4 FragColor;

void main()
{
    // Define the number of colors in the rainbow
    int numColors = 7; // You can adjust this to change the number of colors
    float rainbowWidth = 1.0 / float(numColors);
    
    // Define rainbow colors
    vec3 rainbowColors[7];
    rainbowColors[0] = vec3(1.0, 0.0, 0.0); // Red
    rainbowColors[1] = vec3(1.0, 0.5, 0.0); // Orange
    rainbowColors[2] = vec3(1.0, 1.0, 0.0); // Yellow
    rainbowColors[3] = vec3(0.0, 1.0, 0.0); // Green
    rainbowColors[4] = vec3(0.0, 0.0, 1.0); // Blue
    rainbowColors[5] = vec3(0.5, 0.0, 1.0); // Indigo
    rainbowColors[6] = vec3(1.0, 0.0, 1.0); // Violet
    
    // Calculate the current fragment's position within the rainbow
    float rainbowPosition = mod(gl_FragCoord.x, 1.0) / rainbowWidth;
    int colorIndex = int(rainbowPosition * float(numColors));
    
    // Set the fragment color based on the rainbow position
    FragColor = vec4(rainbowColors[colorIndex], 1.0);
}
