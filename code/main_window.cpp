#include "main_window.hpp" 
#include "util/assert.hpp"
#include "util/deubg_print.hpp"

#include <X11/Xlib.h>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <array>

#include <X11/X.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

void MainWindow::create_display()
{
    display = XOpenDisplay(nullptr);
    if(display == nullptr)
        throw std::runtime_error("[WINDOW] Failed to open XDisplay!");
}
// -------------------------------------------------

void MainWindow::prepare_screen() noexcept
{
    screen    = DefaultScreenOfDisplay(display);
    screen_id = DefaultScreen(display);
}
// -------------------------------------------------

static void validate_glx_version(Display& display)
{

    int major, minor;
    glXQueryVersion(&display, &major, &minor);
    
    if(major <= 1 && minor < 4) 
    {
        XCloseDisplay(&display);
        throw std::runtime_error("[WINDOW] GLX 1.4 or greater is required.\n");
    }
    
    DEBUG_PRINT("[WINDOW] GLX Version: Major = ", major, ", Minor = ", minor);
}
// -------------------------------------------------

static XVisualInfo* setup_glx_visual(Display& display, int screen_id)
{
    std::array<int, 17> attribs {
        GLX_RGBA,
        GLX_DOUBLEBUFFER,
        GLX_DEPTH_SIZE,     24,
        GLX_STENCIL_SIZE,    8,
        GLX_RED_SIZE,        8,
        GLX_GREEN_SIZE,      8,
        GLX_BLUE_SIZE,       8,
        GLX_SAMPLE_BUFFERS,  0,
        GLX_SAMPLES,         0,
        None
    };

    XVisualInfo* visual = glXChooseVisual(&display, screen_id, attribs.data());
    
    if(visual == nullptr)
    {
        XCloseDisplay(&display);
        throw std::runtime_error("[WINDOW] Could not create correct visual window.\n");
    }

    return visual;
}
// -------------------------------------------------

void MainWindow::open_window() noexcept
{
    auto root = RootWindow(display, screen_id);

    window_attribs.border_pixel      = BlackPixel(display, screen_id);
    window_attribs.background_pixel  = WhitePixel(display, screen_id);
    window_attribs.override_redirect = true;
    window_attribs.colormap          = XCreateColormap(display, root, visual->visual, AllocNone);
    window_attribs.event_mask        = ExposureMask | ButtonPressMask;

    window = XCreateWindow(
            display, 
            root, 
            0, 0, 
            screen->width, screen->height, 
            0, 
            visual->depth, 
            InputOutput, 
            visual->visual, 
                CWBackPixel   | 
                CWColormap    | 
                CWBorderPixel | 
                CWEventMask, 
            &window_attribs);
}
// -------------------------------------------------

static void force_window_behind(Display* dpy, Window& window)
{   
    REFUTE_ASSERTION(dpy == nullptr);

    // Finding the atom identifier for the window state.
    // Atom: Always Below Other Windows
    Atom wm_state_below = XInternAtom(dpy, "_NET_WM_STATE_BELOW", 1);
    if(wm_state_below != None)
        DEBUG_PRINT("[WINDOW] _NET_WM_STATE_BELOW has atom of ", static_cast<long int>(wm_state_below));
    else
        throw std::runtime_error("Could not find atom for _NET_WM_STATE_BELOW!\n");

    // Finding the window state atom identifier.
    Atom wm_net_state = XInternAtom(dpy, "_NET_WM_STATE", 1);
    if(wm_net_state != None)
        DEBUG_PRINT("[WINDOW] _NET_WM_STATE has atom of ", static_cast<long int>(wm_net_state));
    else
        throw std::runtime_error("Could not find atom for _NET_WM_STATE!\n");

    if(wm_state_below != None)
    {
        // Setting up a message to X11 to force
        // the window to be behind all of the rest
        // of the windows.
        XClientMessageEvent xclient;
        std::memset(&xclient, 0, sizeof(xclient));
        
        xclient.type         = ClientMessage;
        xclient.window       = window;
        xclient.message_type = wm_net_state;
        xclient.format       = 32;

#ifndef _NET_WM_STATE_ADD
# define _NET_WM_STATE_ADD 1
#endif

        xclient.data.l[0] = _NET_WM_STATE_ADD;
        xclient.data.l[1] = wm_state_below;
        xclient.data.l[2] = 0;
        xclient.data.l[3] = 0;
        xclient.data.l[4] = 0;

        // Update Settings     
        XSendEvent(dpy, DefaultRootWindow(dpy), false, SubstructureRedirectMask | SubstructureNotifyMask, reinterpret_cast<XEvent*>(&xclient)); 
        XFlush(dpy);
    }
}
// -------------------------------------------------

static void remove_bar(Display* dpy, Window& window)
{
    REFUTE_ASSERTION(dpy == nullptr);

    Atom wm_window_type = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE", false);
    if(wm_window_type != None)
        DEBUG_PRINT("[WINDOW] _NET_WM_WINDOW_TYPE has atom of ", static_cast<long int>(wm_window_type));
    else
        throw std::runtime_error("Could not find atom for _NET_WM_WINDOW_TYPE");

    auto value = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_DOCK", false);
    XChangeProperty(dpy, window, wm_window_type, XA_ATOM, 32, PropModeReplace, reinterpret_cast<const unsigned char*>(&value), 1);
}
// -------------------------------------------------

void MainWindow::create()
{
    create_display();
    prepare_screen();
    
    validate_glx_version(*display);
    visual = setup_glx_visual(*display, screen_id);
    open_window();
    force_window_behind(display, window);
    remove_bar(display, window);

    XClearWindow(display, window);
    XMapRaised(display, window);

    window_created = true;
}
// -------------------------------------------------
void MainWindow::handle_events() 
{
    XNextEvent(display, &event);
}

// -------------------------------------------------
void MainWindow::create_opengl_context()
{
    context = glXCreateContext(display, visual, nullptr, true);    
    glXMakeCurrent(display, window, context);

    // Initializing OpenGL
    glewExperimental = true;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("[WINDOW] Failed to initialize GLEW!\n");
    
    DEBUG_PRINT("[OpenGL] Vendor:   " , glGetString(GL_VENDOR));
    DEBUG_PRINT("[OPENGL] Renderer: " , glGetString(GL_RENDERER)); 
    DEBUG_PRINT("[OPENGL] Version:  " , glGetString(GL_VERSION));
    DEBUG_PRINT("[OPENGL] GLSL:     " , glGetString(GL_SHADING_LANGUAGE_VERSION));

    context_created = true;
    glViewport(0, 0, screen->width, screen->height);
}
// -------------------------------------------------

void MainWindow::swap_buffers() {
    glXSwapBuffers(display, window);
}
// -------------------------------------------------

MainWindow::~MainWindow()
{
    if(window_created)
    {
        XFree(visual);
        XFreeColormap(display, window_attribs.colormap);
        XDestroyWindow(display, window);
        XCloseDisplay(display);
        window_created = false;

        if(context_created)
        {
            glXDestroyContext(display, context);
            context_created = false;
        }
    }
}

