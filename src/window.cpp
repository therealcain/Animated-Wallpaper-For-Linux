#include "../include/window.hpp"

#include <GL/glew.h>

#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <X11/X.h>
#include <X11/Xlib.h>

#include <stdexcept>
#include <iostream>
#include <cstring>

namespace awfl {

    [[maybe_unused]]
    static void error_callback(int error, const char* desc) {
        std::cerr << "Error ID: " << error << ", " << desc << std::endl;
    }   
    // -------------------------------------------------

    Window::Window()
    {
        // Initializing GLFW
        if(!glfwInit())
            throw std::runtime_error("Failed to initialize GLFW!\n");

#ifdef BUILD_MODE
        glfwSetErrorCallback(error_callback);
#endif
    }

    Window::~Window()
    {
        // Destroying window if created
        if(created)
        {
            glfwDestroyWindow(window);
            created = false;
        }
        
        // Cleanup GLFW
        glfwTerminate();
    }
    // -------------------------------------------------
   
    static void force_window_behind(GLFWwindow& glfw_window)
    {
        Display* dpy = glfwGetX11Display();
        
        // Finding the atom identifier for the window state.
        // Atom: Always Below Other Windows
        Atom wm_state_below = XInternAtom(dpy, "_NET_WM_STATE_BELOW", 1);
        if(wm_state_below != None)
        {
#ifdef BUILD_MODE
            std::cout << "_NET_WM_STATE_BELOW has atom of " << static_cast<long>(wm_state_below) << std::endl;
#endif
        }
        else
            throw std::runtime_error("Could not find atom for _NET_WM_STATE_ABOVE!\n");

        // Finding the window state atom identifier.
        Atom wm_net_state = XInternAtom(dpy, "_NET_WM_STATE", 1);
        if(wm_net_state != None)
        {
#ifdef BUILD_MODE
            std::cout << "_NET_WM_STATE has atom of " << static_cast<long>(wm_net_state) << std::endl;
#endif
        }
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
            xclient.window       = glfwGetX11Window(&glfw_window);
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

            
            XSendEvent(dpy, DefaultRootWindow(dpy), false, SubstructureRedirectMask | SubstructureNotifyMask, reinterpret_cast<XEvent*>(&xclient)); 
            XFlush(dpy);
        }
    }

    // -------------------------------------------------
    void Window::create()
    {
        // GLFW Minimum versions
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        // Window settings
        glfwWindowHint(GLFW_DECORATED    , false);
        glfwWindowHint(GLFW_RESIZABLE    , false);
        glfwWindowHint(GLFW_FOCUS_ON_SHOW, false);
        glfwWindowHint(GLFW_ICONIFIED    , false);
        glfwWindowHint(GLFW_AUTO_ICONIFY , false);
        glfwWindowHint(GLFW_HOVERED      , true );
        glfwWindowHint(GLFW_FLOATING     , true );

        // Get window dimensions and setup video mode
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwWindowHint(GLFW_RED_BITS    , mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS  , mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS   , mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

        // Try to create window
        // Setting the dimensions as screen dimensions to make
        // borderless fullscreen.
        window = glfwCreateWindow(mode->width, mode->height, "", monitor, nullptr);

        if(window == nullptr)
            throw std::runtime_error("Failed to create window!\n");
        
        force_window_behind(*window);
       
        glfwMakeContextCurrent(window);

        created = true;
    }
    
    // -------------------------------------------------
    bool Window::opened() const {
        return !glfwWindowShouldClose(window);
    }

    // -------------------------------------------------
    void Window::handle_events() {
        glfwPollEvents();
    }
    
    // -------------------------------------------------
    void Window::create_opengl_context()
    {
        // Initializing OpenGL
        glewExperimental = true;
        if(glewInit() != GLEW_OK)
            throw std::runtime_error("Failed to initialize GLEW!\n");

        // Setting the opengl viewport to window size
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);
    }

    // -------------------------------------------------
    void Window::swap_buffers() {
        glfwSwapBuffers(window);
    }


}
