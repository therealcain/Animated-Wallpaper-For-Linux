#include "shader.hpp"

#include "../util/deubg_print.hpp"

#include <GL/glew.h>

#include <fstream>
#include <streambuf>
#include <stdexcept>
#include <vector>

// Creating the vertex and fragment shaders.
static inline auto create_shaders()
{
    struct {
        unsigned int vertex;
        unsigned int fragment;
    } shaders;

    shaders.vertex   = glCreateShader(GL_VERTEX_SHADER);
    shaders.fragment = glCreateShader(GL_FRAGMENT_SHADER);

    return shaders;
}

// Reading the shader file into a string.
static std::string read_shader(std::string_view path)
{
    DEBUG_PRINT("Reading Path: ", path.data());

    std::string out;
    std::ifstream file(path.data(), std::ios::in | std::ios::ate);
    if(file.is_open())
    {
        out.reserve(file.tellg());
        file.seekg(0, std::ios::beg);

        out.assign((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
    }
    else
        throw std::runtime_error("Failed to load shader!\n");

    return out;
}

// Compiling the shader.
static void compile_shader(const std::string& str, unsigned int& ID, [[maybe_unused]] std::string_view path)
{
    DEBUG_PRINT("Compiling shader: ", path.data());
    
    const char* ptr = str.c_str();
    glShaderSource(ID, 1, &ptr, nullptr);
    glCompileShader(ID);
}

// Checking for errors in the compilation.
static void check_shader(unsigned int ID)
{
    int result, info_length;
    glGetShaderiv(ID, GL_COMPILE_STATUS , &result);
    glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &info_length);

    if(info_length > 0) 
    {
#ifdef DEBUG_MODE
        throw std::runtime_error("Shader is incorrect!\n");
#else
        std::vector<char> error_message(info_length + 1);
        glGetShaderInfoLog(ID, info_length, nullptr, &error_message[0]);
        DEBUG_PRINT("Shader Error: ", &error_message[0]);
#endif
    }
}

// Linking the fragment and vertex shaders together.
static unsigned int link_shaders(unsigned int vertexID, unsigned int fragmentID)
{
    DEBUG_PRINT("Linking Shaders!");

    unsigned int programID = glCreateProgram();

    glAttachShader(programID, vertexID);
    glAttachShader(programID, fragmentID);
    
    glLinkProgram(programID);

    return programID;
}

// Detaching the shaders from the program id.
static inline void unlink_shaders(unsigned int programID, unsigned int vertexID, unsigned int fragmentID)
{
    glDetachShader(programID, vertexID);
    glDetachShader(programID, fragmentID);
}

// Deleting the vertex and fragment id.
static inline void delete_shaders(unsigned int vertexID, unsigned int fragmentID)
{
    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
}

unsigned int Shader::load(std::string_view vertex, std::string_view fragment)
{
    auto [vertexID, fragmentID] = create_shaders();

    auto vertexStr   = read_shader(vertex);
    auto fragmentStr = read_shader(fragment);
        
    compile_shader(vertexStr, vertexID, vertex);
    check_shader(vertexID);

    compile_shader(fragmentStr, fragmentID, fragment); 
    check_shader(fragmentID);

    auto programID = link_shaders(vertexID, fragmentID);
    check_shader(programID);

    unlink_shaders(programID, vertexID, fragmentID);
    delete_shaders(vertexID, fragmentID);

    return programID;
}

