/**
 * Created in The 1th of Februrary, 2021 by Eviatar
 * ------------------------------------------------
 * This file is where the window and opengl context
 * are being setted up.
 **/

#pragma once

#include <GL/glew.h>
#include <GL/glx.h>

#include <X11/Xlib.h>

class MainWindow
{
public:
    MainWindow() = default;
    ~MainWindow();
    
    void create();
    constexpr bool opened() const { return true; }
    void handle_events();

    // OpenGL functionalities
    void create_opengl_context();
    void swap_buffers();

private:
    void create_display();
    void prepare_screen() noexcept;
    void open_window() noexcept;

private:
    Display*     display;
    Screen*      screen;
    int          screen_id;
    
    Window               window;
    XSetWindowAttributes window_attribs;

    XEvent event;

    XVisualInfo* visual;
    GLXContext   context;
    
    bool window_created  = false;
    bool context_created = false;
};

