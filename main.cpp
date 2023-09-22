#define STB_IMAGE_IMPLEMENTATION
#include "include/main_program.h"
#include "stb_image.h"
#include <nlohmann/json.hpp>

#ifndef LOG(x)
#define LOG(x) std::cout << x << std::endl;
#endif
#ifndef INFOLOG(x, y)
#define INFOLOG(x, y) std::cerr << x << y << std::endl;
#endif

struct AppConfig {
        int window_width;
        int window_height;
};

GLFWwindow* start_window(AppConfig app_config) {    
    glfwInit();
    glfwWindowHint(GLFW_ALPHA_BITS, 8); // 8 bits for alpha channel
    GLFWwindow* window = glfwCreateWindow(app_config.window_width, app_config.window_height, "OpenGL Textures", NULL, NULL);
    
    glViewport(0, 0, app_config.window_width, app_config.window_height);
    glfwMakeContextCurrent(window);
    glewInit();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    return window;
}

GLuint load_shader_program(GLuint& vertex_shader, GLuint& frag_shader, std::string vs, std::string fs) {
    int success;
    char info_log[512];

    // vertex shader
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vs_c = vs.c_str();
    glShaderSource(vertex_shader, 1, &vs_c, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        INFOLOG("Vertex shader compilation failed:\n", info_log);
    }

    // frag shader
    frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fs_c = fs.c_str();
    glShaderSource(frag_shader, 1, &fs_c, NULL);
    glCompileShader(frag_shader);
    glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(frag_shader, 512, NULL, info_log);
        INFOLOG("Frag shader compilation failed:\n", info_log);
    }

    // shader program
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, frag_shader);
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        INFOLOG("Shader program linking failed:\n", info_log);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(frag_shader);

    return shader_program;
}

void load_vertices(Verts& verts, GLuint& vao, GLuint& vbo, GLuint& vbot, GLuint& ebo) {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verts.vertices.size()* sizeof(float), verts.vertices.data(), GL_STATIC_DRAW);
    // Configure vertex attributes for position (vbo)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &vbot);
    glBindBuffer(GL_ARRAY_BUFFER, vbot);
    glBufferData(GL_ARRAY_BUFFER, verts.tex_coords.size()* sizeof(float), verts.tex_coords.data(), GL_STATIC_DRAW);
    LOG(verts.tex_coords.size());
    // Configure vertex attributes for texture coordinates (vbot)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(verts.indices), verts.indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void load_image(const char* image_path, GLuint& texture) {
    
    int width, height, num_channels;
    unsigned char* data = stbi_load(image_path, &width, &height, &num_channels, 0);
    if (!data) {
        std::cerr << "Failed to load images." << std::endl;
    } else {
        LOG("Width: " << width);
        LOG("Height: " << height);
        LOG("Num_of_Channels: " << num_channels);
    }
    stbi__vertical_flip(data, width, height, num_channels);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);    
    stbi_image_free(data);
}

void run_main_loop(AppConfig& app_config, GLFWwindow* window, GLuint shader_program, Verts& verts, GLuint& vao, GLuint& ebo, GLuint& texture) {
    int gcd = 1;

    for (int i = 1; i <= app_config.window_width && i <= app_config.window_height; ++i) {
        if (app_config.window_width % i == 0 && app_config.window_height % i == 0) {
            gcd = i;
        }
    }
    float x = app_config.window_width / gcd;
    float y = app_config.window_height / gcd;    
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::ortho(-x, x, -y, y);
    glm::mat4 mvp = model * projection;

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);
        glBindVertexArray(vao);

        GLuint mvp_location = glGetUniformLocation(shader_program, "mvp");
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glDrawElements(GL_TRIANGLES, verts.indices.size(), GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "OpenGL error: " << error << std::endl;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}    

int main() {
    AppConfig app_config;
    nlohmann::json config;
    std::ifstream config_file("const/config/config.json");
    if (!config_file.is_open()) {
        INFOLOG("Error opening config.json", "");
        return 1;
    }
    try {
        config_file >> config;
    } catch (const std::exception& e) {
        INFOLOG("Error parsing JSON: ", e.what());
        return 1;
    }
    config_file.close();
    app_config.window_width = config["windowWidth"];
    app_config.window_height = config["windowHeight"];
    LOG("CONFIG LOADED");
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    GLFWwindow* window = start_window(app_config);
    if (window == nullptr) {
        std::cerr << "Failed to create a window" << std::endl;
        glfwTerminate();
        return -1;
    }
    LOG("STARTED WINDOW");
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    std::string vs = read_shader_file("shaders/shader_vs.glsl");
    std::string fs = read_shader_file("shaders/shader_fs.glsl");
    Sprite sprite;
    LOG("LOADED SHADERS");
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    GLuint vertex_shader, frag_shader, shader_program;
    shader_program = load_shader_program(vertex_shader, frag_shader, vs, fs);    
    LOG("COMPILED SHADERS");
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    Verts verts;
    read_data_file("const/data/square.txt", verts);
    GLuint vao, vbo, vbot, ebo;
    load_vertices(verts, vao, vbo, vbot, ebo);    
    LOG("LOADED VERTEX DATA");
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    GLuint texture;
    load_image("src/img/dggl.png", texture);    
    glUseProgram(shader_program);
    GLuint uniform = glGetUniformLocation(shader_program, "our_texture");
    glUniform1i(uniform, 0);    
    LOG("TEXTURES LOADED");
    //////////////////////////////////////////////////////////////////////////////////////////////////
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);    

    run_main_loop(app_config, window, shader_program, verts, vao, ebo, texture);
    
    glfwTerminate();
    return 0;
}