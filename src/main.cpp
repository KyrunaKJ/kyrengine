#include <iostream>
#include <vector>
#include <glm/glm.hpp>

#include "../include/shader_reader.h"
#include "../include/main_program.h"
#include "../include/shape.h"
#include "../include/shape_instance.h"
#include "../include/shape_manager.h"

using namespace std;

#ifndef LOG
#define LOG(x) std::cout << x << endl;
#endif // LOG(x)

#ifdef CMAKE_BUILD
string shader_file_path = "../const/data";
#else 
string shader_file_path = "const/data/";
#endif

#define DEBUG 1

// cd cmake .. && make && ./test

int main() {        
    GLFWwindow* window = StartWindow();
    if (window == nullptr) return -1;
    LOG("Window Loaded");
    
    vector<Shape> shapes;
    vector<string> files = get_dir_files(shader_file_path);
    InitializeShapes(shapes, files);
    LOG("Shapes Loaded");    

    vector<ShapeInstance> render_shapes, render_shapes_two;
    ShapeManager sm(render_shapes, shapes, 0.5f), sm_two(render_shapes_two, shapes, 1.0f);

    // Custom drawing code
    sm.create_square_grid(4);
    sm.create_triangle_grid(2);
    //sm.create_2d_square_array(3, 2, -1.0f);
    //sm.create_2d_triangle_array(3, 2);

    LOG("Shapes Created");    

    GLuint base_shader_program = LoadShaders();
    LOG("Shaders Loaded"); 

    RunMainLoop(window, render_shapes, base_shader_program);

    glfwTerminate();
    LOG("Window Closed");

    return 0;
}