#include "plugin_manager.h"

void PluginManager::addFunc(std::string const& name)
{
    HMODULE hm = LoadLibraryA((path + name).c_str());
    if (!hm)
        throw std::exception();

    std::string function = name.substr(0, name.find(".dll"));
    function.erase(0, 4);

    auto func = (func_type)GetProcAddress(hm, "func");

    if (func)
    {
        func_table.insert(std::pair<std::string, func_type>(function, func));
    }
    else
    {
        throw std::exception();
    }
}

PluginManager::PluginManager()
{
    path = getPath();
    WIN32_FIND_DATAA find;
    HANDLE hFind = FindFirstFileA((path + std::string("*.dll")).c_str(), &find);

    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            std::string file_name(find.cFileName);
            addFunc(file_name);
        } while (NULL != FindNextFileA(hFind, &find));

        FindClose(hFind);
    }
    else
    {
        throw std::exception();
    }
}


bool PluginManager::contains(std::string const& name)
{
    return func_table.contains(name);
}

double PluginManager::function(std::string const& name, double const& value1, double const& value2) {
    if (func_table.contains(name)) {
        try
        {
            double res = func_table[name](value1, value2);
            return res;
        }
        catch (...)
        {
            throw std::exception();
        }
    }
    else
    {
        throw std::exception();
    }
}

std::string PluginManager::getPath()
{
    char P[1000]{};
    if (!getcwd(P, sizeof(P))) throw std::exception();
    std::string full_path = P;
    while (full_path.back() != '\\') full_path.pop_back();
    full_path += std::string("plugins\\");
    return full_path;
}