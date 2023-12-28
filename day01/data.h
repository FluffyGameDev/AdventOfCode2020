#pragma once

#include "types.h"
#include <vector>

namespace AoC
{
    const char* s_testInputData
    {
        "1721\n"
        "979\n"
        "366\n"
        "299\n"
        "675\n"
        "1456"
    };

    struct InputData
    {
        std::vector<u64> Numbers;
    };

    struct OutputData
    {
        u64 TwoNumbersProduct{};
        u64 ThreeNumbersProduct{};
    };
}