#ifndef SHAPE_INSTANCE_H
#define SHAPE_INSTANCE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "appconfig.h"
#include "shape.h"

using namespace std;

struct ShapeInstance {
    Shape shape;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    ShapeInstance(const Shape& s, const glm::vec3& pos) 
        : shape(s), position(pos), rotation(0.0f), scale(1.0f) {}
};

#endif