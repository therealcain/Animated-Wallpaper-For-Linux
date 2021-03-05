/**
 * Created in The 4th of Februrary, 2021 by Eviatar
 * ------------------------------------------------
 * When calling opengl functions this is checking
 * if any of them has errors.
 **/

#pragma once

extern void gl_print_errors(const char* func, const char* file, int line) noexcept;

#ifdef DEBUG_MODE
# if defined(__GNUC__) || defined(__clang__)
#  define GL_LOG(x) do { x; gl_print_errors(#x, __FILE__, __LINE__); } while(false)
# else
#  define GL_LOG(x) do { x; gl_print_errors(#x, "UNKNOWN", -1); } while(false)
# endif
#else
# define GL_LOG(x) do { x; } while(false)
#endif
