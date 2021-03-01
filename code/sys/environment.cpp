#include "environment.hpp"

#include <stdexcept>

const std::string& Environment::get_username()
{
    if(uinfo != nullptr)
    {
        // Just to avoid new memory allocation for the
        // same string over and over again.
        static std::string as_string(uinfo->pw_name);
        return as_string;
    }
    
    throw std::runtime_error("Failed to find username!\n");
}

const fs::path& Environment::get_home_path()
{
    static const std::string path_str = std::string("/home/") + get_username() + "/";
    static const auto path = fs::path(path_str);
    return path;
}

