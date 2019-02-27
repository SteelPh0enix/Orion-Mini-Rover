#pragma once
#include <string.h>

namespace Utility {
inline char last_char(char const* str) { return str[strlen(str) - 1]; }
inline char first_char(char const* str) { return str[0]; }

template <unsigned e>
constexpr int pow(int a) {
  return a * pow<e - 1>(a);
}

template <>
constexpr int pow<0>(int) {
  return 1u;
}

template <>
constexpr int pow<1>(int a) {
  return a;
}

}  // namespace Utility
