#pragma once

#include "types.h"

namespace AoC
{
    template <typename T>
    struct Vector2
    {
        T x;
        T y;

        static T DotProduct(const Vector2& v1, const Vector2& v2)
        {
            return v1.x * v2.x + v1.y * v2.y;
        }

        static T SquareDistance(const Vector2& v1, const Vector2& v2)
        {
            Vector2 diff{ v1.x - v2.x, v1.y - v2.y };
            return DotProduct(diff, diff);
        }

        static T ManhattanDistance(const Vector2& v1, const Vector2& v2)
        {
            Vector2 diff{ v1 - v2 };
            return std::abs(diff.x) + std::abs(diff.y);
        }

        static Vector2 Rotate90DegClockwise(const Vector2& v)
        {
            return { v.y, -v.x };
        }

        static Vector2 Rotate90DegCounterClockwise(const Vector2& v)
        {
            return { -v.y, v.x };
        }

        friend bool operator==(const Vector2& lhs, const Vector2& rhs)
        {
            return lhs.x == rhs.x && lhs.y == rhs.y;
        }

        friend bool operator!=(const Vector2& lhs, const Vector2& rhs)
        {
            return !(lhs == rhs);
        }

        friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
        {
            return { lhs.x + rhs.x, lhs.y + rhs.y };
        }

        friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
        {
            return { lhs.x - rhs.x, lhs.y - rhs.y };
        }
    };

    using Vector2S = Vector2<s32>;
    using Vector2U = Vector2<u32>;
    using Vector2SLL = Vector2<s64>;
    using Vector2ULL = Vector2<u64>;
}