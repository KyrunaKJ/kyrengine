#include "shape.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

void Shape::load_vertices_from_file(const string& file_path) {
    ifstream file(file_path);
    if (!file.is_open()) {
        throw runtime_error("Failed to open file: " + file_path);
    }
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        float vertex_value;
        while (iss >> vertex_value) {
            vertices.push_back(vertex_value);
        }
    }
    file.close();
}

void Shape::create_vbo() {
        GLuint vbo = 0;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        vao = 0;    
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    }