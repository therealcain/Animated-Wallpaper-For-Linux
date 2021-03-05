#include "main_app.hpp"

#include <GL/glew.h>

#include "renderer/video.hpp"

App::App()
{
    window.create();
    window.create_opengl_context();
}

bool App::run()
{
    Video video("video.mp4", 2560, 1440);   
    while(window.opened())
    {
        // OpenGL
        glClear(GL_COLOR_BUFFER_BIT);
//        video.draw();  

        // Window
        window.swap_buffers();
        window.handle_events();
    }

    return true;
}

