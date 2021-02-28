#pragma once

#include <assert.h>

#ifdef DEBUG_MODE
# define AWFL_ASSERT(x) assert(x)
#else
# define AWFL_ASSERT(x)
#endif

#ifdef DEBUG_MODE
# define AWFL_REFUTE_ASSERTION(x) assert(!x)
#else
# define AWFL_REFUTE_ASSERTION(x)
#endif
