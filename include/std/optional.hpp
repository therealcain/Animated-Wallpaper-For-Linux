#pragma once

#if __has_include(<optional>)
# include <optional>
#elif __has_include(<experimental/optional>)
  namespace std { using namespace std::experimental; }
#else
# error "optional could not be found!"
#endif
