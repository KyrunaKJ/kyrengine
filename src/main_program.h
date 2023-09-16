#ifndef MAIN_PROGRAM_H
#define MAIN_PROGRAM_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader_reader.h"

GLFWwindow* StartWindow();
GLuint LoadShaders();

#endif