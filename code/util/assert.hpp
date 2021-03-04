/**
 * Created in The 1th of Februrary, 2021 by Eviatar
 * ------------------------------------------------
 * This file is simply creating a macro for the 
 * assert function to be always in debug mode.
 **/

#pragma once

#include <assert.h>

#ifdef DEBUG_MODE
# define ASSERT(x) assert(x)
#else
# define ASSERT(x)
#endif

#ifdef DEBUG_MODE
# define REFUTE_ASSERTION(x) assert(!(x))
#else
# define REFUTE_ASSERTION(x) do { } while(false)
#endif
