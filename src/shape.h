#ifndef SHAPE_H
#define SHAPE_H

#include <GL/glew.h>
#include <iostream>
#include <vector>

using namespace std;

struct Shape {
    GLuint vao;
    GLenum mode;
    vector<float> vertices;

    Shape(GLenum mode) : vao(0), mode(mode) {}
    Shape(GLenum mode, vector<float> vertices) : vao(0), mode(mode), vertices(vertices) {}

    void load_vertices_from_file(const string&);
    void create_vbo();   
};

#endif