#include <iostream>
#include <vector>

#include "shader_reader.h"
#include "main_program.h"
#include "shape.h"
#include "fps_counter.h"

using namespace std;

#ifndef LOG
#define LOG(x) std::cout << x << endl;
#endif // LOG(x)

#define DEBUG 1

// cd cmake .. && make && ./test

int main() {
    
    GLFWwindow* window = StartWindow();
    LOG("Window Loaded");
    if (window == nullptr) return -1;

    // CREATE TRIANGLE
    vector<float> triangle_points = {
        0.0f,  0.5f,  0.0f, // middle
        0.5f,  -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f // bottom left
    };    
    Shape triangle_shape(GL_TRIANGLES, triangle_points);

    // CREATE SQUARE
    vector<float> square_points = {
            -0.5f, 0.5f,  0.0f, // top left
            0.5f,  0.5f,  0.0f, // top right
            0.5f,  -0.5f, 0.0f, // bottom right
            0.5f,  -0.5f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f, // bottom left
            -0.5f, 0.5f,  0.0f // top left
    };
    Shape square_shape(GL_LINE_STRIP, square_points);

    square_shape.create_vbo();
    triangle_shape.create_vbo();

    vector<Shape> shapes;
    shapes.push_back(square_shape);
    shapes.push_back(triangle_shape);

    GLuint base_shader_program = LoadShaders();
    LOG("Shaders Loaded");
    
    // UPDATE LOOP
    while(!glfwWindowShouldClose(window)) {

        if (DEBUG) {
            update_fps_counter(window);
        }
        // wipe the drawing surface clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // loop through shapes
        for (const auto& shape : shapes) {
            glUseProgram(base_shader_program);
            glBindVertexArray(shape.vao);
            glDrawArrays(shape.mode, 0, shape.vertices.size() / 3);
        }

        // put the stuff we've been drawing onto the display
        glfwSwapBuffers(window);

        // update other events like input handling
        glfwPollEvents();

        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, 1);
        }

    };

    glfwTerminate();

    LOG("Window Closed");

    return 0;
}