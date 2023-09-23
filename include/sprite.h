#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glew.h>
#include "verts.h"
#include "app_config.h"
#include <iostream>

#ifndef LOG(x)
#define LOG(x) std::cout << x << std::endl;
#endif

class Sprite {
public:
    Sprite(AppConfig& app_config, float start_x, float start_y) {
        int gcd = 1;  
        vertices.position = glm::vec3(start_x, start_y, 0.0f);
        for (int i = 1; i <= app_config.window_width && i <= app_config.window_height; ++i) {
            if (app_config.window_width % i == 0 && app_config.window_height % i == 0) {
                gcd = i;
            }
        }
        app_config.max_x = app_config.window_width / gcd;
        app_config.max_y = app_config.window_height / gcd;    
        LOG(app_config.max_x << " " << app_config.max_y);
        model = glm::translate(glm::mat4(1.0f), glm::vec3(start_x, start_y, 0.0f));
        projection = glm::ortho(-app_config.max_x, app_config.max_x, -app_config.max_y, app_config.max_y);
        mvp = model * projection;
    }
    
    void render();
    void move(glm::vec3);
    
    GLuint& get_vao(); 
    GLuint& get_vbo(); 
    GLuint& get_vbot(); 
    GLuint& get_ebo();
    GLuint& get_texture(); 
    GLuint& get_shader_program();
    Verts& get_verts();
    glm::vec3 get_movement();
    glm::mat4 getMVP() {
        return projection * model;
    }
    float get_width() const;
    float get_height() const;
    float get_rotation() const;
    void set_rotation(float);
    void set_vao(GLuint);
    void set_vbo(GLuint);
    void set_vbot(GLuint);
    void set_ebo(GLuint);
    void set_texture(GLuint);
    void set_shader_program(GLuint);
    void set_verts(Verts);
    void set_position(glm::vec3);
    void set_movement(glm::vec3);
    bool moving_right;
    bool moving_up;
    bool is_background;

private:
    GLuint vao, vbo, vbot, ebo, texture, shader_program;
    glm::mat4 mvp, model, projection;
    glm::vec3 movement;
    Verts vertices;
    float rotation_angle;
};

#endif