#pragma once

#include <string>

namespace awfl {

    class DesktopInfo
    {
    public:
        DesktopInfo();
        void fetch_desktop();

    private:
        inline static std::string desktop_folder;
    };

}
