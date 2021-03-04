/**
 * Created in The 4th of Februrary, 2021 by Eviatar
 * ------------------------------------------------
 * This file is simply creating a macro to print
 * in debug, and not in release.
 **/

#pragma once

#include <iostream>

#ifdef DEBUG_MODE
template<typename... Ts> 
void DEBUG_PRINT(const Ts&... ts) 
{
    (std::clog << ... << ts);
    std::clog << std::endl;
}
#else
template<typename... Ts> 
inline void DEBUG_PRINT(const Ts&...) {}
#endif
