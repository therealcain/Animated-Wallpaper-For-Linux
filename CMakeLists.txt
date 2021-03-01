cmake_minimum_required(VERSION 3.7)

project(DesktopEngine)

set(CMAKE_CXX_STANDARD 17)

if(UNIX)
    # Warnings are enabled only for debug mode.
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        add_compile_options(-Wall -Wextra -Wpedantic -O3 -g -lc++fs)
        add_definitions(-DDEBUG_MODE)
    else() # Release Mode
        add_compile_options(-O3 -lc++fs)
    endif()

    # Which desktop envirnoment the user using.
    if(DESKTOP_ENVIRONMENT MATCHES Gnome)
        add_definitions(-DDESKTOP_ENVIRONMENT_GNOME)
    elseif(DESKTOP_ENVIRONMENT MATCHES Mate)
        add_definitions(-DDESKTOP_ENVIRONMENT_MATE)
    else()
        message(FATAL_ERROR "Please specify your desktop envirnoment. (e.g. -DDESKTOP_ENVIRONMENT=Gnome)")
    endif()

    # X11
    find_package(X11 REQUIRED)
    include_directories(${X11_INCLUDE_DIR})
    
    # GLFW
    find_package(glfw3 REQUIRED)

    # OpenGL
    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIR})

    # OpenGL Extension Wrangler
    find_package(GLEW REQUIRED)
    include_directories(${GLEW_INCLUDE_DIR})

    # Compiling
    add_executable(${CMAKE_PROJECT_NAME}
        code/main.cpp
        code/main_app.cpp
        code/main_window.cpp
        code/sys/environment.cpp
        code/sys/desktop_info.cpp
        code/sys/application.cpp
        code/sys/mimeapps.cpp
        code/main_window.hpp
        code/main_app.hpp
        code/sys/environment.hpp
        code/sys/desktop_info.hpp
        code/sys/application.hpp
        code/sys/mimeapps.hpp
        code/util/assert.hpp
        code/std/optional
        code/std/filesystem
        code/std/string_view)

    target_link_libraries(${CMAKE_PROJECT_NAME} ${X11_LIBRARIES} glfw ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

else()
    message(FATAL_ERROR "Your platform is not supported.")
endif()

