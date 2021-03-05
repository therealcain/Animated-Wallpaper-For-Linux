#include "gl_log.hpp"

#include <iostream>
#include "../std/string_view"

#include <GL/glew.h>

#define LIST_OF_OPENGL_ERRORS           \
    X(GL_NO_ERROR)                      \
    X(GL_INVALID_VALUE)                 \
    X(GL_INVALID_OPERATION)             \
    X(GL_STACK_OVERFLOW)                \
    X(GL_STACK_UNDERFLOW)               \
    X(GL_INVALID_FRAMEBUFFER_OPERATION) \
    X(GL_CONTEXT_LOST)                  \
    X(GL_TABLE_TOO_LARGE)

static constexpr std::string_view get_error_as_string(const GLenum error) noexcept
{
    switch(error)
    {
#define X(name) case name: return #name;
        LIST_OF_OPENGL_ERRORS
#undef X
    }

    return "UNDEFINED";
}

void gl_print_errors(const char* func, const char* file, int line) noexcept
{
    GLenum error = glGetError();

    while(error != GL_NO_ERROR)
    {
        std::cerr << "OpenGL Error:\n"
                  << "In Function: " << func << "\n"
                  << "In File: "     << file << "\n"
                  << "In Line: "     << line << "\n"
                  << "Type: "        << get_error_as_string(error)
                  << std::endl;

        error = glGetError();
    }
}


