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
# define REFUTE_ASSERTION(x)
#endif
