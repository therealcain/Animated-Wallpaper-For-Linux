/**
 * Created in The 4th of Februrary, 2021 by Eviatar
 * ------------------------------------------------
 * This file loads the shaders, and gives the
 * functionality to operate them easily.
 **/

#pragma once

#include "../std/string_view"

class Shader
{
public:
    void load(std::string_view vertex_path, std::string_view fragment_path);
    void bind();

    inline unsigned int id() { return m_id; }

    ~Shader();

private:
    unsigned int m_id;
};
