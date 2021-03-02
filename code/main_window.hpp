/**
 * Created in The 1th of Februrary, 2021 by Eviatar
 * ------------------------------------------------
 * This file is where the window and opengl context
 * are being setted up.
 **/

#pragma once

class GLFWwindow;

class MainWindow
{
public:
    MainWindow();
    ~MainWindow();
    
    void create();
    bool opened() const;
    void handle_events();

    // OpenGL functionalities
    void create_opengl_context();
    void swap_buffers();

private:
    GLFWwindow* window = nullptr;
    bool created = false;
};

