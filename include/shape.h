#ifndef SHAPE_H
#define SHAPE_H

#include <GL/glew.h>
#include <iostream>
#include <vector>
#include "appconfig.h"

using namespace std;

struct Verts {
    vector<float> position;
    vector<float> uv;
    vector<float> color;
    vector<float> bone;
};

struct Shape {
    GLuint vao;
    GLenum mode;
    Verts vertices;

    Shape(const string& file_path, AppConfig& config) : vao(0) { load_vertices_from_file(file_path, config); }
    Shape(GLenum mode) : vao(0), mode(mode) {}

    void load_vertices_from_file(const string&, AppConfig&);
    void load_texture_vertices_from_file(const string&, AppConfig&);
    void create_vbo();   
};


#endif