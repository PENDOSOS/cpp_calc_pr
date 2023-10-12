#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <Windows.h>
#include <vector>
#include <direct.h> 

using func_type = double(*)(double, double);

class PluginManager {
    std::string path;
    std::unordered_map<std::string, func_type> func_table;
    void addFunc(std::string const& name);
    std::string getPath();
public:
    PluginManager();
    double function(const std::string& name, double const& value1, double const& value2 = 0);
    bool contains(std::string const& name);
};