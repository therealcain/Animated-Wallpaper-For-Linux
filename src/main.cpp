#include "../include/window.hpp"

#include <iostream>
#include <GL/glew.h>

#include "../include/env.hpp"
int main()
{
    awfl::Window window;
    window.create();
    window.create_opengl_context();

    std::cout << awfl::Env::get_username().value() << std::endl;

    while(window.opened())
    {
        // OpenGL
        glClear(GL_COLOR_BUFFER_BIT);

        // Window
        window.handle_events();
        window.swap_buffers();
    }
}
