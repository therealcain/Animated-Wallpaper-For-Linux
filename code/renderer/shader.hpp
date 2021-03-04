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
    static unsigned int load(std::string_view vertex, std::string_view fragment);
};
