#include "config_reader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

Config readConfig(const std::string& configFile) {
    Config config;

    std::ifstream file(configFile);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string key, value;
            if (std::getline(iss, key, '=') && std::getline(iss, value)) {
                if (key == "Name") {
                    config.pipeName = value;
                }
            }
        }
        file.close();
    } else {
        std::cerr << "Error opening configuration file: " << configFile << std::endl;
    }

    return config;
}
