cmake_minimum_required(VERSION 3.7)

project(AWFP)

set(CMAKE_CXX_STANDARD 17)

if(UNIX)
    # Warnings are enabled only for debug mode.
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        add_compile_options(-Wall -Wextra -Wpedantic)
        add_definitions(-DDEBUG_MODE)
    endif()

    # X11
    find_package(X11 REQUIRED)
    include_directories(${X11_INCLUDE_DIR})

    # XCB
    # find_package(XCB REQUIRED)
    # include_directories(${XCB_INCLUDE_DIR})

    # OpenGL
    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIR})

    # OpenGL Extension Wrangler
    find_package(GLEW REQUIRED)
    include_directories(${GLEW_INCLUDE_DIR})

    # Compiling
    add_executable(${CMAKE_PROJECT_NAME}
        src/main.cpp)

    target_link_libraries(${CMAKE_PROJECT_NAME} ${X11_LIBRARIES} ${XCB_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

else()
    message(FATAL_ERROR "Your platform is not supported.")
endif()

