
#include "../include/main_program.h"

#define LOG(x) std::cout << x << std::endl;
#define INFOLOG(x, y) std::cerr << x << y << std::endl;

std::string read_shader_file(const char* file_path) {
    std::string shader_code;
    std::ifstream shader_file;
    shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shader_file.open(file_path);
        std::stringstream shader_stream;
        shader_stream << shader_file.rdbuf();
        shader_file.close();
        shader_code = shader_stream.str();
    } catch (std::ifstream::failure e) {
        std::cerr << "Error: Failed to read shader file: " << file_path << std::endl;
    }
    return shader_code;
}

void read_data_file(const char* file_path, Verts& verts) {
    std::ifstream file(file_path);
    if (!file) {
        INFOLOG("Error: Failed to open a file - ", file_path);
        return;
    }

    std::string line;
    bool reading_vertices = true;
    while(std::getline(file, line)) {
        if (line.substr(0, 2) == "//") {
            continue;
        }

        if (line.empty()) {
            reading_vertices = false;
            continue;
        }

        std::istringstream iss(line);
        float value;
        int count = 0;
        while (iss >> value) {
            if (reading_vertices) {
                if (count < 3) {
                    verts.vertices.push_back(value);
                } else { 
                    verts.tex_coords.push_back(value);
                }
            } else {
                verts.indices.push_back(static_cast<GLuint>(value));
            }
            count++;
        }
    }
}

