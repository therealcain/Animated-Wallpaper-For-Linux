/**
 * Created in The 2th of Februrary, 2021 by Eviatar
 * ------------------------------------------------
 * This file is file saves all of the application in
 * the desktops along with their locations and size.
 **/

#pragma once

#include <vector>

#include "application.hpp"

class DesktopInfo
{
public:
    void clear();
    void load();

private:
    using AppVec = std::vector<Application>;
    AppVec apps;
};

