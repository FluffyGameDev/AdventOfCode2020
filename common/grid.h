#pragma once

#include <vector>
#include "vector2.h"

namespace AoC
{
    template <typename T>
    struct Grid
    {
        std::vector<T> Data;
        Vector2S Size;

        u64 ComputeFlatIndex(const Vector2S& position) const
        {
            return position.x + (u64)position.y * Size.x;
        }

        bool IsInGrid(const Vector2S& position) const
        {
            return position.x >= 0 && position.y >= 0 && position.x < Size.x && position.y < Size.y;
        }
    };
}