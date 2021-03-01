#pragma once

#if __has_include(<filesystem>)
# include <filesystem>
#elif __has_include(<experimental/filesystem>)
# include <experimental/filesystem>
  namespace std { using namespace std::experimental; }
#else
# error "string_view could not be found!"
#endif

namespace fs = std::filesystem;
