#ifndef MAIN_PROGRAM_H
#define MAIN_PROGRAM_H  

#include <unistd.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "verts.h"
#include "sprite.h"

std::string read_shader_file(const char*);

void read_data_file(const char*, Verts&);

#endif