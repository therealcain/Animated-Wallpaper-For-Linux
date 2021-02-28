#pragma once

#include <string>

namespace de {

    class DesktopInfo
    {
    public:
        DesktopInfo();
        void fetch_desktop();

    private:
        inline static std::string desktop_folder;
    };

}
