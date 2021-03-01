#include "application.hpp"
#include "../util/assert.hpp"

#include <cstdlib>

Application::Application(
    const std::wstring& name, 
    const std::string& path, std::string& icon_path,
    const std::string& exec_command)
        : m_name(name), 
          m_path(path), m_icon_path(icon_path), 
          m_exec_command(exec_command)
{
    REFUTE_ASSERTION(m_name.empty());
    REFUTE_ASSERTION(m_path.string().empty());
    REFUTE_ASSERTION(m_icon_path.string().empty());
    REFUTE_ASSERTION(m_exec_command.empty());
}

bool Application::execute() {
    return system(m_exec_command.c_str()) == -1 ? false : true; 
}

