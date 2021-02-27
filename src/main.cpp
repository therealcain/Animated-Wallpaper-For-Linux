#include "../include/window.hpp"
#include <GLFW/glfw3.h>

int main()
{

    awfl::Window window;
    window.create();
    window.create_opengl_context();

    while(window.opened())
    {
        window.handle_events();
        
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.f);

        window.swap_buffers();
    }
}
