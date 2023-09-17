#include "../../include/main_program.h"
#include "../../include/fps_counter.h"
#include "../../include/appconfig.h"
#include "../../include/shape_instance.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <unistd.h>
#include <iostream>
#include <filesystem>

#ifndef LOG
#define LOG(x) cout << x << endl;
#endif

#define DEBUG 1

#ifdef CMAKE_BUILD
const string shader_file_path = "../const/";
const string config_file_path = "../";
#else 
const string shader_file_path = "const/";
const string config_file_path = "";
#endif

GLFWwindow* StartWindow() {
    AppConfig config;
    config.load(config_file_path + "config.json");
    
    if (!glfwInit()) {
        LOG("ERROR: could not start GLFW3\n");
        return nullptr;
    }

    GLFWwindow* window = glfwCreateWindow(config.windowWidth, config.windowHeight, "Hello GL", NULL, NULL);
    if (!window) {
        LOG("ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    return window;
}

GLuint LoadShaders() {
    const string vertexShader = ShaderReader(shader_file_path + "shader_vs.glsl").source;    
    const string fragShader = ShaderReader(shader_file_path + "shader_fs.glsl").source;

    GLchar* vertex_shader = (GLchar*)vertexShader.c_str();
    GLchar* frag_shader = (GLchar*)fragShader.c_str();    
    
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &frag_shader, NULL);
    glCompileShader(fs);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, fs);
    glAttachShader(shader_program, vs);
    glLinkProgram(shader_program);

    return shader_program;
}

GLenum det_shape_mode(vector<float>& vertices) {
    if (vertices.size() % 6 == 0) {
        LOG("Making square");
        return GL_LINE_STRIP;
    } else if (vertices.size() % 9 == 0) {
        LOG("Making triangle");
        return GL_TRIANGLES; 
    } else {
        // Handle unsupported vertex count
        throw std::runtime_error("Unsupported number of vertices");
    }
}

vector<string> get_dir_files(string& dir_path) {
    std::vector<std::string> file_names;
    try {
        for (const auto& entry : filesystem::directory_iterator(dir_path)) {
            if (entry.is_regular_file()) {
                file_names.push_back(entry.path().filename().string());
            }
        }
    } catch (const filesystem::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return file_names;
}

void InitializeShapes(vector<Shape>& shapes, vector<string>& files) {
    AppConfig config;
    config.load(config_file_path + "config.json");
    
    for (string str : files) {
        Shape shape(shader_file_path + "data/" + str, config);
        shape.mode = det_shape_mode(shape.vertices);
        shape.create_vbo();
        shapes.push_back(shape);
    }
}

// Function to calculate the greatest common divisor (GCD) of two numbers
float gcd(float a, float b) {
    while (std::abs(b) > 0.001f) {
        float temp = b;
        b = std::fmod(a, b);
        a = temp;
    }
    return a;
}

void aspectRatioToRatio(float width, float height, float& x, float& y) {
    float divisor = gcd(width, height);
    x = width / divisor;
    y = height / divisor;
}

void RenderShapes(vector<ShapeInstance>& shapes, GLuint shader_program, float width, float height) {
    GLuint modelMatrixID = glGetUniformLocation(shader_program, "modelMatrix");    
    GLuint projectionMatrixID = glGetUniformLocation(shader_program, "projectionMatrix");

    float x, y;
    aspectRatioToRatio(width, height, x, y);

    LOG(x);
    LOG(y);

    glm::mat4 projection = glm::ortho(-x, x, -y, y, -1.0f, 1.0f);

    glUseProgram(shader_program);

    glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projection[0][0]);

    // loop through shapes
    for (const auto& shape : shapes) {
        glBindVertexArray(shape.shape.vao);

        glm::mat4 model = glm::translate(glm::mat4(1.0f), shape.position);

        glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &model[0][0]);

        glDrawArrays(shape.shape.mode, 0, shape.shape.vertices.size() / 3);
    }
}

void RunMainLoop(GLFWwindow* window, vector<ShapeInstance>& shapes, GLuint shader_program) {
    glUseProgram(shader_program);

    AppConfig config;
    config.load(config_file_path + "config.json");
    float aspectratio = (float)config.windowWidth / (float)config.windowHeight;    
    LOG(aspectratio);

    glViewport(0, 0, config.windowWidth, config.windowHeight);
    
    // UPDATE LOOP
    while(!glfwWindowShouldClose(window)) {

        if (DEBUG) {
            update_fps_counter(window);
        }
        // wipe the drawing surface clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        RenderShapes(shapes, shader_program, config.windowWidth, config.windowHeight);

        // put the stuff we've been drawing onto the display
        glfwSwapBuffers(window);

        // update other events like input handling
        glfwPollEvents();

        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, 1);
        }
    };
}