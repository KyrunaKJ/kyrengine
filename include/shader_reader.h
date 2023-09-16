#ifndef SHADER_READER_H
#define SHADER_READER_H

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

struct ShaderReader {
    ShaderReader(string);
    string source;
};

#endif