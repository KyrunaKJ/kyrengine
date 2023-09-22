#include "../../include/sprite.h"

GLuint Sprite::get_vao() {
    return vao;
}
	
GLuint Sprite::get_vbo() {
    return vbo;
}
	
GLuint Sprite::get_vbot() {
    return vbot;
}
	
GLuint Sprite::get_ebo() {
    return ebo;
}
	
GLuint Sprite::get_texture() {
    return texture;
}
	
GLuint Sprite::get_shader_program() {
    return shader_program;
}

Verts Sprite::get_verts() {
    return vertices;
}
	
void Sprite::set_vao(GLuint value) {
    vao = value;
}
	
void Sprite::set_vbo(GLuint value) {
    vbo = value;
}
	
void Sprite::set_vbot(GLuint value) {
    vbot = value;
}
	
void Sprite::set_ebo(GLuint value) {
    ebo = value;
}
	
void Sprite::set_texture(GLuint value) {
    texture = value;
}
	
void Sprite::set_shader_program(GLuint value) {
    shader_program = value;
}

void Sprite::set_verts(Verts value) {
    vertices = value;
}