#include "../include/environment.hpp"

#include <unistd.h>
#include <pwd.h>

#include <stdexcept>

namespace awfl {

    std::string Environment::get_username()
    {
        static const uid_t uid = geteuid();
        static const passwd* pw = getpwuid(uid);
    
        if(pw)
            return std::string(pw->pw_name);
        
        throw std::runtime_error("Failed to find username!\n");
    }
}
