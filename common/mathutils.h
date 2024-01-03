#pragma once

#include "types.h"

namespace AoC::Math
{
    template <typename T>
    s32 Sign(T val)
    {
        return (T(0) < val) - (val < T(0));
    }

    u64 PopulationCount(u64 x)
    {
        x -= (x >> 1) & 0x5555555555555555;
        x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
        x = (x + (x >> 4)) & 0x0f0f0f0f0f0f0f0f;
        return (x * 0x0101010101010101) >> 56;
    }
}