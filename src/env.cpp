#include "../include/env.hpp"

#include <unistd.h>
#include <pwd.h>

#include <stdexcept>

namespace awfl {

    std::optional<std::string> Env::get_username()
    {
        const uid_t uid = geteuid();
        const passwd* pw = getpwuid(uid);
        
        if(pw)
            return std::string(pw->pw_name);

        return {};
    }
}
