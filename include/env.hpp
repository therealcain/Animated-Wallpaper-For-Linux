#pragma once

#include <string>
#include <optional>

namespace awfl {

    // Environment
    class Env
    {
    public:
        static std::optional<std::string> get_username();
    };

}
