cmake_minimum_required(VERSION 3.7)

project(DesktopEngine)

set(CMAKE_CXX_STANDARD 17)

if(UNIX)
    # Warnings are enabled only for debug mode.
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        add_compile_options(-Wall -Wextra -Wpedantic -O3 -g)
        add_definitions(-DDEBUG_MODE)
    else() # Release Mode
        add_compile_options(-O3)
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
        src/main.cpp
        src/app.cpp
        src/window.cpp
        src/environment.cpp
        src/desktop_info.cpp
        include/window.hpp
        include/app.hpp
        include/environment.hpp
        include/desktop_info.hpp
        include/util/assert.hpp
        include/std/optional.hpp
        include/std/filesystem.hpp
        include/std/string_view.hpp)

    target_link_libraries(${CMAKE_PROJECT_NAME} ${X11_LIBRARIES} glfw ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

else()
    message(FATAL_ERROR "Your platform is not supported.")
endif()

