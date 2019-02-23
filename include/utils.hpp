#pragma once
#include <string.h>

namespace Utility {
inline char last_char(char const* str) { return str[strlen(str) - 1]; }
inline char first_char(char const* str) { return str[0]; }
}  // namespace Utility