
#define STB_IMAGE_IMPLEMENTATION
#include "../include/main_program.h"
#define LOG(x) std::cout << x << std::endl;
#define INFOLOG(x, y) std::cerr << x << y << std::endl;

std::string read_shader_file(const char* file_path) {
    std::string shader_code;
    std::ifstream shader_file;
    shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shader_file.open(file_path);
        std::stringstream shader_stream;
        shader_stream << shader_file.rdbuf();
        shader_file.close();
        shader_code = shader_stream.str();
    } catch (std::ifstream::failure e) {
        std::cerr << "Error: Failed to read shader file: " << file_path << std::endl;
    }
    return shader_code;
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

void load_vertices(Sprite& sprite) {
    glGenVertexArrays(1, &sprite.get_vao());
    glBindVertexArray(sprite.get_vao());

    glGenBuffers(1, &sprite.get_vbo());
    glBindBuffer(GL_ARRAY_BUFFER, sprite.get_vbo());
    glBufferData(GL_ARRAY_BUFFER, sprite.get_verts().vertices.size()* sizeof(float), sprite.get_verts().vertices.data(), GL_STATIC_DRAW);
    // Configure vertex attributes for position (vbo)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &sprite.get_vbot());
    glBindBuffer(GL_ARRAY_BUFFER, sprite.get_vbot());
    glBufferData(GL_ARRAY_BUFFER, sprite.get_verts().tex_coords.size()* sizeof(float), sprite.get_verts().tex_coords.data(), GL_STATIC_DRAW);
    //LOG(sprite.get_verts().tex_coords.size());
    // Configure vertex attributes for texture coordinates (vbot)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &sprite.get_ebo());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite.get_ebo());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sprite.get_verts().indices), sprite.get_verts().indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
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

GLFWwindow* start_window(AppConfig& app_config) {    
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

void run_main_loop(GLFWwindow* window, AppConfig& app_config, std::vector<Sprite>& sprites) {
    auto startTime = std::chrono::high_resolution_clock::now();
    float deltaTime = 0.0f; // Time elapsed since the last frame

    float speed = 1.0f;   // Movement speed
    
    while (!glfwWindowShouldClose(window)) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<float>(currentTime - startTime).count();
        startTime = currentTime;

        glClear(GL_COLOR_BUFFER_BIT);

        for (Sprite& sprite : sprites) {
            sprite.move(sprite.get_movement() * deltaTime);
            sprite.render();

            // Check if the sprite has reached the right edge
            if (sprite.get_verts().position.x + (sprite.get_width() / 2)  >= app_config.max_x) {
                sprite.moving_right = false;
            }            

            // Check if the sprite has reached the left edge
            if (sprite.get_verts().position.x - (sprite.get_width() / 2) <= -app_config.max_x) {
                sprite.moving_right = true;
            }

            // Update movement direction based on bounce
            if (sprite.moving_right) {
                sprite.set_movement(glm::vec3(speed, 0.0f, 0.0f));
            } else {
                sprite.set_movement(glm::vec3(-speed, 0.0f, 0.0f));
        }
    }

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "OpenGL error: " << error << std::endl;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}    

void read_data_file(const char* file_path, Verts& verts) {
    std::ifstream file(file_path);
    if (!file) {
        INFOLOG("Error: Failed to open a file - ", file_path);
        return;
    }

    std::string line;
    bool reading_vertices = true;
    while(std::getline(file, line)) {
        if (line.substr(0, 2) == "//") {
            continue;
        }

        if (line.empty()) {
            reading_vertices = false;
            continue;
        }

        std::istringstream iss(line);
        float value;
        int count = 0;
        while (iss >> value) {
            if (reading_vertices) {
                if (count < 3) {
                    verts.vertices.push_back(value);
                } else { 
                    verts.tex_coords.push_back(value);
                }
            } else {
                verts.indices.push_back(static_cast<GLuint>(value));
            }
            count++;
        }
    }
}

