#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <string>
using namespace std;

class AppConfig {
    public:
    int windowWidth;
    int windowHeight;

    AppConfig();

    void load(const string& config_file);
    void save(const string& config_file);
};

#endif