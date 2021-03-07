/**
 * Created in The 1th of Februrary, 2021 by Eviatar
 * ------------------------------------------------
 * This file is where the window and opengl context
 * are being setted up.
 **/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <X11/Xlib.h>

class MainWindow
{
public:
    MainWindow() = default;
    ~MainWindow();
    
    void create();
    void handle_events();
    static auto get_monitor_size();

    constexpr bool opened() const       { return true;      }
    inline void clear()                 { window.clear();   }
    inline void draw(sf::Drawable& obj) { window.draw(obj); }
    inline void display()               { window.display(); }

private:
    void create_xdisplay();
    void create_xwindow();
    void create_xview();
    void show_xwindow() noexcept;

private:
    struct {
        Display* display = nullptr;
        Window window;
        Window view;
        int screen_id;
        bool opened;
    } x11;
    
    sf::RenderWindow window;
};

