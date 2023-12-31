#pragma once

#include <string>
#include <vector>
#include "range.h"

namespace AoC
{
    const char* s_testInputData
    {
        "BFFFBBFRRR\n"
        "FFFBBBFRRR\n"
        "BBFFBBFRLL"
    };

    struct InputData
    {
        std::vector<std::string> BoardingPasses{};
    };

    struct OutputData
    {
        RangeU64 SeatIdRange{};
        u64 MissingSeatId{};
    };
}