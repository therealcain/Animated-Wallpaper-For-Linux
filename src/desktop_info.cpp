#include "../include/desktop_info.hpp"
#include "../include/environment.hpp"

#include <stdexcept>
#include <iostream>
#include <vector>

namespace awfl {

    DesktopInfo::DesktopInfo()
    {
        const auto username = Environment::get_username();
        desktop_folder = std::string("/home/") + username + "/Desktop/"; 
    }

    void DesktopInfo::fetch_desktop()
    {
    }
}
