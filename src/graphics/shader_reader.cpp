#include "../../include/shader_reader.h"

#ifndef LOG
#define LOG(x) cout << x << endl;
#endif

ShaderReader::ShaderReader(string name) {
    string line, allLines;
    ifstream fileStream(name);

    if (fileStream.is_open()) {
        while (getline(fileStream, line)) {
            allLines += line + "\n";
        }

        source = allLines;

        fileStream.close();
    } else LOG("File couldn't be opened");
}