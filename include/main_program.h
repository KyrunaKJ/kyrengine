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
vector<GLuint> LoadShaders();
void InitializeShapes(vector<Shape>&, vector<string>&);
void RenderShapes(vector<vector<ShapeInstance>> &, vector<GLuint>&, float, float);
void RenderSimpleColorShapes(GLuint, vector<ShapeInstance>&, float, float);
void RenderTextureShapes(GLuint, vector<ShapeInstance>&, float, float);
void RunMainLoop(GLFWwindow*, vector<vector<ShapeInstance>> &, vector<GLuint>&);

#endif