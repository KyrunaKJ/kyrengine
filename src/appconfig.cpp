#include "appconfig.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

AppConfig::AppConfig() : windowWidth(800), windowHeight(600) {

}

void AppConfig::load(const string& config_file) {
    ifstream file(config_file);
    if (file.is_open()) {
        nlohmann::json jsonConfig;
        file >> jsonConfig;
        file.close();

        windowWidth = jsonConfig["windowWidth"];
        windowHeight = jsonConfig["windowHeight"];
    } else {
        cerr << "Failed to open config file: " << config_file << endl;
    }    
}

void AppConfig::save(const string& config_file) {
    nlohmann::json jsonConfig;
    jsonConfig["windowWidth"] = windowWidth;
    jsonConfig["windowHeight"] = windowHeight;

    std::ofstream file(config_file);
    if (file.is_open()) {
        file << jsonConfig.dump(4);
        file.close();
    } else {
        cerr << "Failed to open configuration file for writing: " << config_file << endl;
    }
}