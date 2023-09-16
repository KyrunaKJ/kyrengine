#include <iostream>
#include <vector>

#include "../include/shader_reader.h"
#include "../include/main_program.h"
#include "../include/shape.h"

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

    GLuint base_shader_program = LoadShaders();
    LOG("Shaders Loaded");    
    
    RunMainLoop(window, shapes, base_shader_program);

    glfwTerminate();
    LOG("Window Closed");

    return 0;
}