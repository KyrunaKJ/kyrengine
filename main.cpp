#include "include/main_program.h"
#include <nlohmann/json.hpp>

#ifndef LOG(x)
#define LOG(x) std::cout << x << std::endl;
#endif

#ifndef INFOLOG(x, y)
#define INFOLOG(x, y) std::cerr << x << y << std::endl;
#endif

int main() {
    AppConfig app_config;
    nlohmann::json config;
    std::ifstream config_file("const/config/config.json");
    if (!config_file.is_open()) {
        INFOLOG("Error opening config.json", "");
        return 1;
    } else {
        try {
            config_file >> config;
        } catch (const std::exception& e) {
            INFOLOG("Error parsing JSON: ", e.what());
            return 1;
        }
    }
    config_file.close();
    app_config.window_width = config["windowWidth"];
    app_config.window_height = config["windowHeight"];
    LOG("CONFIG LOADED: Window Width - " << app_config.window_width);
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
    std::string bfs = read_shader_file("shaders/shader_fs_backup.glsl");
    std::string fs = read_shader_file("shaders/shader_fs.glsl");
    LOG("LOADED SHADERS");
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    Sprite base_sprite(app_config, 0.0f, 0.0f);    
    Sprite backup_sprite(app_config, 0.0f, 0.0f);
    GLuint vertex_shader, frag_shader, b_frag_shader;
    backup_sprite.set_shader_program(load_shader_program(vertex_shader, b_frag_shader, vs, bfs));
    base_sprite.set_shader_program(load_shader_program(vertex_shader, frag_shader, vs, fs));
    LOG("COMPILED SHADERS");
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    read_data_file("const/data/square.txt", backup_sprite.get_verts());
    for (float& value : backup_sprite.get_verts().vertices) {
        value *= 2.0f;
    }
    read_data_file("const/data/square.txt", base_sprite.get_verts());
    load_vertices(backup_sprite);
    load_vertices(base_sprite);
    LOG("LOADED VERTEX DATA");
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    load_image("src/img/dggl.png", base_sprite.get_texture());    
    glUseProgram(base_sprite.get_shader_program());
    GLuint uniform = glGetUniformLocation(base_sprite.get_shader_program(), "our_texture");
    glUniform1i(uniform, 0);    
    LOG("TEXTURES LOADED");
    //////////////////////////////////////////////////////////////////////////////////////////////////
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);    
    std::vector<Sprite> sprites;
    base_sprite.set_movement(glm::vec3(1.0f, 0.0f, 0.0f));
    //backup_sprite.set_movement(glm::vec3(-1.0f, 0.0f, 0.0f));
    backup_sprite.moving_right = false;
    
    sprites.push_back(backup_sprite);
    sprites.push_back(base_sprite);
    run_main_loop(window, app_config, sprites);    
    glfwTerminate();
    return 0;
}