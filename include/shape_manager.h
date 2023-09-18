#ifndef SHAPE_MANAGER_H
#define SHAPE_MANAGER_H

#include <vector>
#include <glm/glm.hpp>
#include "shape_instance.h"

class ShapeManager {
public:
    ShapeManager(vector<ShapeInstance>&, vector<Shape>&);

    void create_square(float, float);

    void create_1d_square_array(int, float);

    void create_2d_square_array(int, int, float);

    void create_square_grid(int, float);

    const vector<ShapeInstance>& get_shapes() const; 

private:
    vector<ShapeInstance>& shapes_;
    vector<Shape>& shape_refs_;
};

#endif