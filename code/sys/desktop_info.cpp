#include "desktop_info.hpp"
#include "environment.hpp"

#include <stdexcept>
#include <iostream>
#include <vector>
#include "../std/filesystem"

void DesktopInfo::clear() {
    apps.clear();
}

void DesktopInfo::load() 
{
    static const fs::path desktop_path = Environment::get_home_path() / fs::path("Desktop/");
    for(auto& p : fs::directory_iterator(desktop_path)) 
    {
    }
}

