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

    # Dekstop envirnoment is Gnome based.
    if(DESKTOP_ENVIRONMENT MATCHES Gnome 
    OR DESKTOP_ENVIRONMENT MATCHES Mate 
    OR DESKTOP_ENVIRONMENT MATCHES Unity
    OR DESKTOP_ENVIRONMENT MATCHES Cinnamon)
        add_definitions(-DBASED_DESKTOP_ENVIRONMENT_GNOME)
        set(BASED_DESKTOP_ENVIRONMENT_GNOME)
        
        if(DESKTOP_ENVIRONMENT MATCHES Gnome)        # Gnome
            add_definitions(-DDESKTOP_ENVIRONMENT_GNOME)
        elseif(DESKTOP_ENVIRONMENT MATCHES Mate)     # Mate
            add_definitions(-DDESKTOP_ENVIRONMENT_MATE)
        elseif(DESKTOP_ENVIRONMENT MATCHES Unity)    # Unity
            add_definitions(-DDESKTOP_ENVIRONMENT_UNITY)
        elseif(DESKTOP_ENVIRONMENT MATCHES Cinnamon) # Cinnamon
            add_definitions(-DDESKTOP_ENVIRONMENT_Cinnamon)
        endif()
    else()
        message(FATAL_ERROR "Please specify your desktop envirnoment. (e.g. -DDESKTOP_ENVIRONMENT=Gnome)")
    endif()

    # pkg-config
    find_package(PkgConfig REQUIRED)

    # X11
    find_package(X11 REQUIRED)
    include_directories(${X11_INCLUDE_DIR})
   
    # OpenGL
    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIR})

    # OpenGL Extension Wrangler
    find_package(GLEW REQUIRED)
    include_directories(${GLEW_INCLUDE_DIR})

    # GL Mathematics
    # find_package(GLM REQUIRED)
    # include_directories(${GLM_INCLUDE_DIR})

    # Video Lan Client
    # find_package(VLC REQUIRED)
    # include_directories(${VLC_INCLUDE_DIR})

    # Include Gnome libs
    if(DEFINED BASED_DESKTOP_ENVIRONMENT_GNOME)
        # Glib 2.0
        pkg_check_modules(GLIB REQUIRED glib-2.0)
        include_directories(${GLIB_INCLUDE_DIRS})
    
        # GIO 2.0
        pkg_check_modules(GIO REQUIRED gio-unix-2.0)
        include_directories(${GIO_INCLUDE_DIRS})
    endif()

    # Compiling
    add_executable(
        ${CMAKE_PROJECT_NAME}
            code/main.cpp
            code/main_app.cpp
            code/main_window.cpp
            
            code/sys/environment.cpp
            
            code/renderer/shader.cpp
            code/renderer/gl_log.cpp
            code/renderer/video.cpp

            code/main_window.hpp
            code/main_app.hpp

            code/sys/environment.hpp

            code/renderer/shader.hpp
            code/renderer/gl_log.hpp
            code/renderer/video.hpp

            code/util/assert.hpp
            code/util/deubg_print.hpp

            code/std/optional
            code/std/filesystem
            code/std/string_view
            
            libs/stb_image.h)

        target_link_libraries(${CMAKE_PROJECT_NAME} ${X11_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} vlc)

    # Link Gnome libs
    if(DEFINED BASED_DESKTOP_ENVIRONMENT_GNOME)
        target_link_libraries(${CMAKE_PROJECT_NAME} ${GLIB_LDFLAGS} ${GIO_LDFLAGS})
    endif()

else()
    message(FATAL_ERROR "Your platform is not supported.")
endif()

