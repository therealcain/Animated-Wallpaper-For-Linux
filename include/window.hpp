#pragma once

#include <cstdint>

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

    private:
        GLFWwindow* window = nullptr;
        bool created = false;
    };

}

