#pragma once

#include <string>

struct Config {
    std::string pipeName;
};

Config readConfig(const std::string& configFile);
