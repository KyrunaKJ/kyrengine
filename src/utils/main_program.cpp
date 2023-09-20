#define STB_IMAGE_IMPLEMENTATION
#include "../../include/stb_image.h"
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

static GLuint texName;

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

vector<GLuint> LoadShaders() {
    vector<GLuint> shaders;
    
    const string vertexShader = ShaderReader(shader_file_path + "shader_vs.glsl").source; 
    const string vertexShadertwo = ShaderReader(shader_file_path + "shader_vs_text.glsl").source;   
    const string fragShader = ShaderReader(shader_file_path + "shader_fs.glsl").source;
    const string texShader = ShaderReader(shader_file_path + "shader_ts.glsl").source;

    GLchar* vertex_shader = (GLchar*)vertexShader.c_str();
    GLchar* vertex_shader_two = (GLchar*)vertexShadertwo.c_str();
    GLchar* frag_shader = (GLchar*)fragShader.c_str();  
    GLchar* tex_shader = (GLchar*)texShader.c_str();  
    
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);

    GLuint vs2 = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs2, 1, &vertex_shader_two, NULL);
    glCompileShader(vs2);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &frag_shader, NULL);
    glCompileShader(fs);

    GLuint ts = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(ts, 1, &tex_shader, NULL);
    glCompileShader(ts);

    int width, height, num_channels;
    unsigned char* data = stbi_load("../const/img/smile.png", &width, &height, &num_channels, 0);

    if (data) {
        LOG("img loaded");
    }

    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);  

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vs);
    glAttachShader(shader_program, fs);
    glLinkProgram(shader_program);
    shaders.push_back(shader_program);

    GLuint shader_program_textures = glCreateProgram();
    glAttachShader(shader_program_textures, vs2);
    glAttachShader(shader_program_textures, ts);
    glLinkProgram(shader_program_textures);
    shaders.push_back(shader_program_textures);    
    
    return shaders;
}

GLenum det_shape_mode(vector<float>& vertices) {
    int vertex_count = vertices.size();
    if (vertex_count > 35) vertex_count -= 9;
    vertex_count /= 3;

    if (vertex_count % 12 == 0) {
        LOG("Making circle");
        return GL_TRIANGLE_FAN; 
    } else if (vertex_count % 4 == 0) {
        LOG("Making square");
        return GL_LINE_STRIP;
    } else if (vertex_count % 3 == 0) {
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
        shape.mode = det_shape_mode(shape.vertices.position);
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

void RenderShapes(vector<vector<ShapeInstance>> & shapes, vector<GLuint>& shader_program, float width, float height) {
    float x, y;
    aspectRatioToRatio(width, height, x, y);

    RenderSimpleColorShapes(shader_program[0], shapes[0], x, y);

    RenderTextureShapes(shader_program[1], shapes[1], x, y);
}

void RenderSimpleColorShapes(GLuint shader, vector<ShapeInstance>& shapes, float proj_x, float proj_y) {
    glUseProgram(shader);
    GLuint modelMatrixID = glGetUniformLocation(shader, "modelMatrix"); 
    GLuint projectionMatrixID = glGetUniformLocation(shader, "projectionMatrix");    

    glm::mat4 projection = glm::ortho(-proj_x, proj_x, -proj_y, proj_y, -1.0f, 1.0f);   

    glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projection[0][0]);

    // loop through shapes
    for (const auto& shape : shapes) {
      glBindVertexArray(shape.shape.vao);

      glm::mat4 model = glm::translate(glm::mat4(1.0f), shape.position);
      
      model = glm::scale(model, shape.scale);

      glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &model[0][0]);

      glDrawArrays(shape.shape.mode, 0, shape.shape.vertices.position.size() / 3);
    }
}

void RenderTextureShapes(GLuint shader, vector<ShapeInstance>& shapes, float proj_x, float proj_y) {
    glUseProgram(shader);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    GLuint modelMatrixID = glGetUniformLocation(shader, "modelMatrixText"); 
    GLuint projectionMatrixID = glGetUniformLocation(shader, "projectionMatrixText");  
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texName);  
    glUniform1i(glGetUniformLocation(shader, "smile_text"), 0);

    glm::mat4 projection = glm::ortho(-proj_x, proj_x, -proj_y, proj_y, -1.0f, 1.0f);   

    glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projection[0][0]);

    // loop through shapes
    for (const auto& shape : shapes) {
        glBindVertexArray(shape.shape.vao);

        glm::mat4 model = glm::translate(glm::mat4(1.0f), shape.position);
      
        model = glm::scale(model, shape.scale);

        glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &model[0][0]);

        glDrawArrays(shape.shape.mode, 0, shape.shape.vertices.position.size() / 3);
    }
    glDisable(GL_TEXTURE_2D);
}

void RunMainLoop(GLFWwindow* window, vector<vector<ShapeInstance>> & shapes, vector<GLuint>& shader_program) {
    AppConfig config;
    config.load(config_file_path + "config.json");
    float aspectratio = (float)config.windowWidth / (float)config.windowHeight;

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