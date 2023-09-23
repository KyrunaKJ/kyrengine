#ifndef VERTS_H
#define VERTS_H

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Verts {
    std::vector<float> vertices, tex_coords, colors;
    std::vector<GLuint> indices;
    glm::vec3 position;
};

#endif