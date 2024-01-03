#pragma once

#include <string>
#include <vector>
#include "types.h"

namespace AoC
{
    const char* s_testInputData
    {
        "abc\n"
        "\n"
        "a\n"
        "b\n"
        "c\n"
        "\n"
        "ab\n"
        "ac\n"
        "\n"
        "a\n"
        "a\n"
        "a\n"
        "a\n"
        "\n"
        "b"
    };

    struct GroupData
    {
        std::vector<std::string> RawAnswers;
    };

    struct InputData
    {
        std::vector<GroupData> Groups;
    };

    struct OutputData
    {
        u64 SumGroupAnswerCount{};
        u64 SumCommonAnswerCount{};
    };
}