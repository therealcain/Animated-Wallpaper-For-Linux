#include "../include/window.hpp"
#include "../include/desktop_info.hpp"

#include <GL/glew.h>

int main()
{
    awfl::Window window;
    window.create();
    window.create_opengl_context();

    awfl::DesktopInfo info;
    info.fetch_desktop();

    while(window.opened())
    {
        // OpenGL
        glClear(GL_COLOR_BUFFER_BIT);

        glClearColor(1.f, 0.5f, 0.5f, 1.f);

        // Window
        window.handle_events();
        window.swap_buffers();
    }
}

