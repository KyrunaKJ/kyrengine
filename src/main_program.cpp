#include "main_program.h"
#include <unistd.h>

#ifndef LOG
#define LOG(x) cout << x << endl;
#endif

#ifdef CMAKE_BUILD
const string shader_file_path = "../const/";
#else 
const string shader_file_path = "const/";
#endif

GLFWwindow* StartWindow() {
    if (!glfwInit()) {
        LOG("ERROR: could not start GLFW3\n");
        return nullptr;
    }

    GLFWwindow* window = glfwCreateWindow(500, 500, "Hello GL", NULL, NULL);
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
    const string vertex_shader_path = shader_file_path + "shader_vs.glsl";
    LOG(vertex_shader_path);
    const string vertexShader = ShaderReader(shader_file_path + "shader_vs.glsl").source;    
    const string fragShader = ShaderReader(shader_file_path + "shader_fs.glsl").source;

    char buf[128];
    LOG(getcwd(buf, sizeof(buf)));

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
