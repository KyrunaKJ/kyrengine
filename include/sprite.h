#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glew.h>
#include "verts.h"
#include "app_config.h"

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
        float x = app_config.window_width / gcd;
        float y = app_config.window_height / gcd;    
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 projection = glm::ortho(-x, x, -y, y);
        mvp = model * projection;
    }
    
    void render();
    
    GLuint& get_vao(); 
    GLuint& get_vbo(); 
    GLuint& get_vbot(); 
    GLuint& get_ebo();
    GLuint& get_texture(); 
    GLuint& get_shader_program();
    Verts& get_verts();
    void set_vao(GLuint);
    void set_vbo(GLuint);
    void set_vbot(GLuint);
    void set_ebo(GLuint);
    void set_texture(GLuint);
    void set_shader_program(GLuint);
    void set_verts(Verts);

private:
    GLuint vao, vbo, vbot, ebo, texture, shader_program;
    glm::mat4 mvp;
    Verts vertices;
};

#endif