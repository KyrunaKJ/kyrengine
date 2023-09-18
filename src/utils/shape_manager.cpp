#include "../../include/shape_manager.h"

ShapeManager::ShapeManager(vector<ShapeInstance>& siv, vector<Shape>& sv) : shapes_(siv), shape_refs_(sv) {};

void ShapeManager::create_square(float x, float y) {
    ShapeInstance si(shape_refs_[1], glm::vec3(x, y, 0.0f));
    shapes_.push_back(si);
}

void ShapeManager::create_1d_square_array(int count, float spacing = 1.0f) {
    for (int i = 0; i < count; i++) {
        create_square(i * spacing, 0.0f);
    }
}

void ShapeManager::create_2d_square_array(int rows, int columns, float spacing = 1.0f) {
    for(int i = 0; i < rows ; i++) {
        for(int j = 0; j < columns ; j++) {
            create_square(j * spacing, -i * spacing);
        }
    }
}

void ShapeManager::create_square_grid(int size, float spacing = 1.0f) {
    create_2d_square_array(size, size, spacing);
}

const vector<ShapeInstance>& ShapeManager::get_shapes() const { return shapes_; }
