#pragma once

#include <string>

#include <unistd.h>
#include <pwd.h>

#include "../std/filesystem"

namespace de {

    class Environment
    {
    public:
        Environment()                   = delete;
        Environment(const Environment&) = delete;
        Environment(Environment&&)      = delete;

        static const std::string& get_username();
        static const fs::path& get_home_path();

    private:
        inline static const uid_t   uid   = geteuid();
        inline static const passwd* uinfo = getpwuid(uid);
    };

}
