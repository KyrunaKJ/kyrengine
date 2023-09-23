#ifndef MAIN_PROGRAM_H
#define MAIN_PROGRAM_H  

#include <unistd.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "verts.h"
#include "sprite.h"
#include "../stb_image.h"

void load_vertices(Sprite&);

void load_image(const char*, GLuint&);

void read_data_file(const char*, Verts&);

void run_main_loop(GLFWwindow*, AppConfig&, std::vector<Sprite>&);

GLFWwindow* start_window(AppConfig&);

std::string read_shader_file(const char*);

GLuint load_shader_program(GLuint&, GLuint&, std::string, std::string);

#endif