#include "../../include/shape.h"
#include <vector>
#include <limits>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

#ifndef LOG
#define LOG(x) cout << x << endl;
#endif

void Shape::load_vertices_from_file(const string& file_path, AppConfig& config) {
    ifstream file(file_path);
    if (!file.is_open()) {
        throw runtime_error("Failed to open file: " + file_path);
    }
    string line;
    float aspectratio = static_cast<float>(config.windowWidth) / static_cast<float>(config.windowHeight);

    while (getline(file, line)) {
        istringstream iss(line);
        float x, y, z;

        if (iss >> x >> y >> z) {                       
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
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