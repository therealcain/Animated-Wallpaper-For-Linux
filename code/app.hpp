#pragma once

#include "window.hpp"

namespace de {

    class App
    {
    public:
        App();
        bool run();

    private:
        Window window;
    };

}
