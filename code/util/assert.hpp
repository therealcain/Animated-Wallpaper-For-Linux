#pragma once

#include <assert.h>

#ifdef DEBUG_MODE
# define DE_ASSERT(x) assert(x)
#else
# define DE_ASSERT(x)
#endif

#ifdef DEBUG_MODE
# define DE_REFUTE_ASSERTION(x) assert(!x)
#else
# define DE_REFUTE_ASSERTION(x)
#endif
