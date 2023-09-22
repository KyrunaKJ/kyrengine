#ifndef VERTS_H
#define VERTS_H

#include <vector>
#include <GL/glew.h>

struct Verts {
    std::vector<float> vertices, tex_coords;
    std::vector<GLuint> indices;
};

#endif