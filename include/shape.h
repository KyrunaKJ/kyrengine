#ifndef SHAPE_H
#define SHAPE_H

#include <GL/glew.h>
#include <iostream>
#include <vector>
#include "appconfig.h"

using namespace std;

struct Shape {
    GLuint vao;
    GLenum mode;
    vector<float> vertices;

    Shape(const string& file_path, AppConfig& config) : vao(0) { load_vertices_from_file(file_path, config); }
    Shape(GLenum mode) : vao(0), mode(mode) {}
    Shape(GLenum mode, vector<float> vertices) : vao(0), mode(mode), vertices(vertices) {}

    void load_vertices_from_file(const string&, AppConfig&);
    void create_vbo();   
};

#endif