#include "environment.hpp"

#include <unistd.h>
#include <pwd.h>

#include <stdexcept>

namespace de {

    const std::string& Environment::get_username()
    {
        // This may break if the user changed his
        // username, app restart is required.
        static const uid_t uid = geteuid();
        static const passwd* pw = getpwuid(uid);
    
        if(pw)
        {
            // Just to avoid new memory allocation for the
            // same string over and over again.
            static std::string as_string(pw->pw_name);
            return as_string;
        }
        
        throw std::runtime_error("Failed to find username!\n");
    }

}
