#pragma once

#include <string>
#include <vector>
#include "range.h"

namespace AoC
{
    const char* s_testInputData
    {
        "1-3 a: abcde\n"
        "1-3 b: cdefg\n"
        "2-9 c: ccccccccc"
    };

    struct PasswordData
    {
        std::string Password{};
        RangeU64 ExpectedCount{};
        char ExpectedChar{};
    };

    struct InputData
    {
        std::vector<PasswordData> PasswordsData;
    };

    struct OutputData
    {
        s64 ValidPasswordCount{};
        s64 ValidPasswordCountNewRules{};
    };
}