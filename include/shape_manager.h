#ifndef SHAPE_MANAGER_H
#define SHAPE_MANAGER_H

#include <vector>
#include <glm/glm.hpp>
#include "shape_instance.h"

class ShapeManager {
public:
    ShapeManager(vector<ShapeInstance>&, vector<Shape>&, float);

    void create_square(float, float = 1.0f);

    void create_horizontal_square_array(int, float = 1.0f);

    void create_vertical_square_array(int, float = 1.0f);

    void create_2d_square_array(int, int, float = 1.0f);

    void create_square_grid(int, float = 1.0f);

    void create_triangle(float, float = 1.0f);

    void create_horizontal_triangle_array(int, float = 1.0f);

    void create_vertical_triangle_array(int, float = 1.0f);

    void create_2d_triangle_array(int, int, float = 1.0f);

    void create_triangle_grid(int, float = 1.0f);

    void create_circle(float, float = 1.0f);

    void create_horizontal_circle_array(int, float = 1.0f);

    void create_vertical_circle_array(int, float = 1.0f);

    void create_2d_circle_array(int, int, float = 1.0f);

    void create_circle_grid(int, float = 1.0f);

    const vector<ShapeInstance>& get_shapes() const; 

private:
    vector<ShapeInstance>& shapes_;
    vector<Shape>& shape_refs_;
    float scale_;
};

#endif