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

