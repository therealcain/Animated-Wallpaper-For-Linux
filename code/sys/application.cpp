#include "application.hpp"
#include "../util/assert.hpp"

#include <cstdlib>

namespace de {

    Application::Application(
        const std::wstring& name, 
        const std::string& path, std::string& icon_path,
        const std::string& exec_command)
            : m_name(name), 
              m_path(path), m_icon_path(icon_path), 
              m_exec_command(exec_command)
    {
        DE_REFUTE_ASSERTION(m_name.empty());
        DE_REFUTE_ASSERTION(m_path.filename() == "");
        DE_REFUTE_ASSERTION(path.empty());
        DE_REFUTE_ASSERTION(m_exec_command.empty());
    }

    bool Application::execute() {
        return system(m_exec_command.c_str()) == -1 ? false : true; 
    }
}

