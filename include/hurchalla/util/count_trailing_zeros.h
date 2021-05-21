// --- This file is distributed under the MIT Open Source License, as detailed
// by the file "LICENSE.TXT" in the root of this repository ---

#ifndef HURCHALLA_UTIL_COUNT_TRAILING_ZEROS_H_INCLUDED
#define HURCHALLA_UTIL_COUNT_TRAILING_ZEROS_H_INCLUDED


#include "hurchalla/util/traits/ut_numeric_limits.h"
#include "hurchalla/util/programming_by_contract.h"
#include "hurchalla/util/compiler_macros.h"
#include <cstdint>
#include <type_traits>
#ifdef _MSC_VER
#  include <intrin.h>
#endif

namespace hurchalla {


template <typename T>
HURCHALLA_FORCE_INLINE int count_trailing_zeros(T x)
{
    static_assert(ut_numeric_limits<T>::is_integer, "");
    static_assert(!ut_numeric_limits<T>::is_signed, "");
    // the overloads should handle the types listed below
    static_assert(!std::is_same<T, std::uint8_t>::value, "");
    static_assert(!std::is_same<T, std::uint16_t>::value, "");
    static_assert(!std::is_same<T, std::uint32_t>::value, "");
    static_assert(!std::is_same<T, std::uint64_t>::value, "");
    HPBC_PRECONDITION2(x != 0);
    int count = 0;
    while ((x & 1) == 0) {
        x = x >> 1;
        ++count;
    }
    return count;
}

// From the gcc docs:
// "Returns the number of trailing 0-bits in x, starting at the least
// significant bit position.  If x is 0, the result is undefined."
HURCHALLA_FORCE_INLINE int count_trailing_zeros(unsigned int x)
{
    HPBC_PRECONDITION2(x != 0);
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, x);
    return static_cast<int>(index);
#else
    return __builtin_ctz(x);
#endif
}

// From the gcc docs:
// "Similar to __builtin_ctz, except the argument type is unsigned long."
HURCHALLA_FORCE_INLINE int count_trailing_zeros(unsigned long x)
{
    HPBC_PRECONDITION2(x != 0);
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, x);
    return static_cast<int>(index);
#else
    return __builtin_ctzl(x);
#endif
}

// From the gcc docs:
// "Similar to __builtin_ctz, except the argument type is unsigned long long."
HURCHALLA_FORCE_INLINE int count_trailing_zeros(unsigned long long x)
{
    HPBC_PRECONDITION2(x != 0);
#ifdef _MSC_VER
    static_assert(sizeof(unsigned long long) == sizeof(unsigned __int64), "");
    unsigned long index;
    _BitScanForward64(&index, x);
    return static_cast<int>(index);
#else
    return __builtin_ctzll(x);
#endif
}

// The following overloads don't have builtin equivalents, but we can just
// use the unsigned int versions
HURCHALLA_FORCE_INLINE int count_trailing_zeros(unsigned short x)
{
    HPBC_PRECONDITION2(x != 0);
    return count_trailing_zeros(static_cast<unsigned int>(x));
}
HURCHALLA_FORCE_INLINE int count_trailing_zeros(unsigned char x)
{
    HPBC_PRECONDITION2(x != 0);
    return count_trailing_zeros(static_cast<unsigned int>(x));
}


} // end namespace

#endif
