#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glew.h>
#include "verts.h"

class Sprite {
public:
    GLuint get_vao(); 
    GLuint get_vbo(); 
    GLuint get_vbot(); 
    GLuint get_ebo();
    GLuint get_texture(); 
    GLuint get_shader_program();
    Verts get_verts();
    void set_vao(GLuint);
    void set_vbo(GLuint);
    void set_vbot(GLuint);
    void set_ebo(GLuint);
    void set_texture(GLuint);
    void set_shader_program(GLuint);
    void set_verts(Verts);

private:
    GLuint vao, vbo, vbot, ebo, texture, shader_program;
    Verts vertices;
};

#endif