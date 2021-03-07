#include "main_app.hpp"

App::App()
{
    window.create();
}

bool App::run()
{
    while(window.opened())
    {
        window.handle_events();
        
        window.clear();
        window.display();
    }

    return true;
}

