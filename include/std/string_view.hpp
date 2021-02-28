#pragma once

#if __has_include(<string_view>)
# include <string_view>
#elif __has_include(<experimental/string_view>)
# include <experimental/string_view>
  namespace std { using namespace std::experimental; }
#else
# error "string_view could not be found!"
#endif
