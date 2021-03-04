#include "main_app.hpp"

#include <GL/glew.h>

App::App()
{
    window.create();
    window.create_opengl_context();
}

bool App::run()
{
    while(window.opened())
    {
        // OpenGL
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.f, 0.f, 1.f, 1.f);

        // Window
        window.handle_events();
        window.swap_buffers();
    }

    return true;
}

