/**
 * Created in The 4th of Februrary, 2021 by Eviatar
 * ------------------------------------------------
 * This file is simply creating a macro to print
 * in debug, and not in release.
 **/

#pragma once

#include <iostream>

#ifdef DEBUG_MODE
# define DEBUG_PRINT(...) fprintf(stderr, __VA_ARGS__, "\n")
#else
# define DEBUG_PRINT(...) do { } while(false)
#endif
