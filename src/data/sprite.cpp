#include "../../include/sprite.h"

void Sprite::render() {
    glUseProgram(shader_program);
    glBindVertexArray(vao);

    GLuint mvp_location = glGetUniformLocation(shader_program, "mvp");
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(getMVP()));
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glDrawElements(GL_TRIANGLES, vertices.indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void Sprite::move(glm::vec3 movement) {
    set_position(get_verts().position + movement);
    model = glm::translate(model, movement);
}

GLuint& Sprite::get_vao() {
    return vao;
}
	
GLuint& Sprite::get_vbo() {
    return vbo;
}
	
GLuint& Sprite::get_vbot() {
    return vbot;
}
	
GLuint& Sprite::get_ebo() {
    return ebo;
}
	
GLuint& Sprite::get_texture() {
    return texture;
}
	
GLuint& Sprite::get_shader_program() {
    return shader_program;
}

Verts& Sprite::get_verts() {
    return vertices;
}

glm::vec3 Sprite::get_movement() {
    return movement;
}

float Sprite::get_width() const {
    // Calculate the sprite's width based on its vertices
    float minX = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::min();

    // Iterate through the vertices to find the minimum and maximum X coordinates
    for (size_t i = 0; i < vertices.vertices.size(); i += 3) {
        float x = vertices.vertices[i];
        if (x < minX) {
            minX = x;
        }
        if (x > maxX) {
            maxX = x;
        }
    }

    // Calculate and return the width
    return maxX - minX;
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

void Sprite::set_position(glm::vec3 value) {
    vertices.position = value;
}

void Sprite::set_movement(glm::vec3 value) {
    movement = value;
}