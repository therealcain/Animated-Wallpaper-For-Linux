/**
 * Created in The 2th of Februrary, 2021 by Eviatar
 * ------------------------------------------------
 * This file is a class that saves all of the 
 * necessary information of the mimemapps.
 **/

#pragma once

#include <string>
#include "../std/filesystem"

class Application
{
public:
    Application() = default;
    Application(
        const std::wstring& name, 
        const std::string& path, std::string& icon_path,
        const std::string& exec_command);

    inline const std::wstring& name        () const { return m_name;         }
    inline const fs::path&     path        () const { return m_path;         }
    inline const fs::path&     icon_path   () const { return m_icon_path;    }
    inline const std::string&  exec_command() const { return m_exec_command; }

    inline void set_exec_command(const std::string& command) { m_exec_command = command; }
    bool execute();

private:
    std::wstring m_name;
    fs::path     m_path;
    fs::path     m_icon_path;
    std::string  m_exec_command;
};

