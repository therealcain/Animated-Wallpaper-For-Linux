#include "main_window.hpp" 
#include "util/assert.hpp"
#include "util/deubg_print.hpp"

#include <SFML/Window/VideoMode.hpp>

#include <X11/X.h>
#include <X11/Xatom.h>

#include <limits>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <array>
#include <numeric>

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
        XSendEvent(
            dpy, 
            DefaultRootWindow(dpy), 
            false, 
            SubstructureRedirectMask | SubstructureNotifyMask, 
            reinterpret_cast<XEvent*>(&xclient));

        XFlush(dpy);
    }
}
// -------------------------------------------------

static void remove_bar_and_dock(Display* dpy, Window& window)
{
    REFUTE_ASSERTION(dpy == nullptr);

    Atom wm_window_type = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE", false);
    if(wm_window_type != None)
        DEBUG_PRINT("[WINDOW] _NET_WM_WINDOW_TYPE has atom of ", static_cast<long int>(wm_window_type));
    else
        throw std::runtime_error("Could not find atom for _NET_WM_WINDOW_TYPE\n");

    auto value = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_DOCK", false);
    XChangeProperty(dpy, window, wm_window_type, XA_ATOM, 32, PropModeReplace, reinterpret_cast<const unsigned char*>(&value), 1);
}
// -------------------------------------------------

auto MainWindow::get_monitor_size()
{
    struct {
        uint16_t width, height;
    } size {
        static_cast<uint16_t>(sf::VideoMode::getDesktopMode().width),
        static_cast<uint16_t>(sf::VideoMode::getDesktopMode().height)
    };

    return size;
}
// -------------------------------------------------

void MainWindow::create_xdisplay()
{
    // Opening up a connection to the X server.
    x11.display = XOpenDisplay(nullptr);
    if(x11.display == nullptr)
        throw std::runtime_error("Failed to create XDisplay!\n");

    // Default screen.
    x11.screen_id = DefaultScreen(x11.display);
}
// -------------------------------------------------

void MainWindow::create_xwindow()
{
    // Creates the main window.
    XSetWindowAttributes attributes;
    attributes.background_pixel = BlackPixel(x11.display, x11.screen_id);
    attributes.event_mask = KeyPressMask;
    x11.window = XCreateWindow(
        x11.display, 
        RootWindow(x11.display, x11.screen_id), 
        0, 0, 
        get_monitor_size().width, get_monitor_size().height, 
        0, 
        DefaultDepth(x11.display, x11.screen_id), 
        InputOutput, 
        DefaultVisual(x11.display, x11.screen_id), 
        CWBackPixel | CWEventMask, 
        &attributes);

    if(!x11.window)
        throw std::runtime_error("Failed to create XWindow!\n");

    XStoreName(x11.display, x11.window, "Better Desktop");
}
// -------------------------------------------------

void MainWindow::create_xview()
{
    // Creates a window that will serve the SFML view.
    x11.view = XCreateWindow(
        x11.display,
        x11.window,
        0, 0,
        get_monitor_size().width, get_monitor_size().height,
        0,
        DefaultDepth(x11.display, x11.screen_id),
        InputOutput,
        DefaultVisual(x11.display, x11.screen_id),
        0,
        nullptr);
}
// -------------------------------------------------

void MainWindow::show_xwindow() noexcept
{
    XMapWindow(x11.display, x11.window);
    XMapWindow(x11.display, x11.view);
    XFlush(x11.display);
}
// -------------------------------------------------

void MainWindow::create()
{
    create_xdisplay();
    create_xwindow();    
    create_xview();
    force_window_behind(x11.display, x11.window);
    remove_bar_and_dock(x11.display, x11.window);
    show_xwindow();

    window.create(x11.view);
}

// -------------------------------------------------
void MainWindow::handle_events() 
{
    while(XPending(x11.display))
    {
        XEvent event;
        XNextEvent(x11.display, &event);
    }
}

// -------------------------------------------------

MainWindow::~MainWindow()
{
    if(x11.opened)
    {
        // Disconnect
        XCloseDisplay(x11.display);
        x11.opened = false;
    }
}


