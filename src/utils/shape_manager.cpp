#include "../../include/shape_manager.h"

ShapeManager::ShapeManager(vector<ShapeInstance>& siv, vector<Shape>& sv, float sc) : shapes_(siv), shape_refs_(sv), scale_(sc) {};

void ShapeManager::create_square(float x, float y) {    
    ShapeInstance si(shape_refs_[1], glm::vec3(x, y, 0.0f));
    si.scale = glm::vec3(scale_);
    si.position *= si.scale;
    shapes_.push_back(si);
}

void ShapeManager::create_horizontal_square_array(int count, float spacing) {
    for (int i = 0; i < count; i++) {
        create_square(i * spacing, 0.0f);
    }
}

void ShapeManager::create_vertical_square_array(int count, float spacing) {
    for (int i = 0; i < count; i++) {
        create_square(0.0f, -i * spacing);
    }
}

void ShapeManager::create_2d_square_array(int rows, int columns, float spacing) {
    for(int i = 0; i < rows ; i++) {
        for(int j = 0; j < columns ; j++) {
            create_square(j * spacing, -i * spacing);
        }
    }
}

void ShapeManager::create_square_grid(int size, float spacing) {
    create_2d_square_array(size, size, spacing);
}

void ShapeManager::create_triangle(float x, float y) {
    ShapeInstance si(shape_refs_[0], glm::vec3(x, y, 0.0f));
    si.scale = glm::vec3(scale_);
    si.position *= si.scale;
    shapes_.push_back(si);
}

void ShapeManager::create_horizontal_triangle_array(int count, float spacing) {
    for (int i = 0; i < count; i++) {
        create_triangle(i * spacing, 0.0f);
    }
}

void ShapeManager::create_vertical_triangle_array(int count, float spacing) {
    for (int i = 0; i < count; i++) {
        create_triangle(0.0f, -i * spacing);
    }
}

void ShapeManager::create_2d_triangle_array(int rows, int columns, float spacing) {
    for(int i = 0; i < rows ; i++) {
        for(int j = 0; j < columns ; j++) {
            create_triangle(j * spacing, -i * spacing);
        }
    }
}

void ShapeManager::create_triangle_grid(int size, float spacing) {
    create_2d_triangle_array(size, size, spacing);
}

const vector<ShapeInstance>& ShapeManager::get_shapes() const { return shapes_; }
