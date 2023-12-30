#pragma once

#include "grid.h"

namespace AoC
{
    const char* s_testInputData
    {
        "..##.......\n"
        "#...#...#..\n"
        ".#....#..#.\n"
        "..#.#...#.#\n"
        ".#...##..#.\n"
        "..#.##.....\n"
        ".#.#.#....#\n"
        ".#........#\n"
        "#.##...#...\n"
        "#...##....#\n"
        ".#..#...#.#"
    };

    struct InputData
    {
        Grid<char> Map;
    };

    struct OutputData
    {
        u64 TestTreeHitCount{};
        u64 TreeHitCountProduct{};
    };
}