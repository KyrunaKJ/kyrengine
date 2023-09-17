#ifndef MAIN_PROGRAM_H
#define MAIN_PROGRAM_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader_reader.h"
#include "shape.h"
#include "shape_instance.h"

vector<string> get_dir_files(string&);
GLFWwindow* StartWindow();
GLuint LoadShaders();
void InitializeShapes(vector<Shape>&, vector<string>&);
void RenderShapes(vector<ShapeInstance>&, GLuint, float, float);
void RunMainLoop(GLFWwindow*, vector<ShapeInstance>&, GLuint);

#endif