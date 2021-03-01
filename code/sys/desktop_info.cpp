#include "desktop_info.hpp"
#include "environment.hpp"

#include <stdexcept>
#include <iostream>
#include <vector>

namespace de {

    DesktopInfo::DesktopInfo()
    {
        const auto username = Environment::get_username();
        home_path = std::string("/home/") + username + "/"; 
    }

    void DesktopInfo::fetch_desktop()
    {
        
    }
}
