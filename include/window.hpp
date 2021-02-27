#pragma once

// Forward declaration
// to avoid including glfw everywhere
class GLFWwindow;

namespace awfl {

    class Window
    {
    public:
        Window();
        ~Window();
        
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

}

