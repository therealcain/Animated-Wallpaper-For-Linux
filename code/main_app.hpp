/**
 * Created in The 2th of Februrary, 2021 by Eviatar
 * ------------------------------------------------
 * This file is the starting point of the entire 
 * software, it handles the configurations and 
 * the rendering loop.
 **/

#pragma once

#include "main_window.hpp"

class App
{
public:
    App();
    bool run();

private:
    MainWindow window;
};
