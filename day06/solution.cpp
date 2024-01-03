#include "data.h"
#include "aoc.h"

#include <numeric>
#include "mathutils.h"

namespace AoC
{
    namespace Internal
    {
        u64 AggregateAnswers(const std::string& answers)
        {
            u64 result{};
            for (char c : answers)
            {
                result |= 1ULL << (c - 'a');
            }

            return result;
        }

        u64 AggregateGroupAnswers(const GroupData& group)
        {
            u64 result{};
            for (const std::string& answers : group.RawAnswers)
            {
                result |= AggregateAnswers(answers);
            }

            return result;
        }

        u64 AggregateCommonAnswers(const GroupData& group)
        {
            u64 result{ AggregateAnswers(group.RawAnswers[0]) };
            for (const std::string& answers : group.RawAnswers)
            {
                result &= AggregateAnswers(answers);
            }

            return result;
        }
    }

    bool ReadInput(std::istream& inputStream, InputData& inputData, const AoCContext& context)
    {
        std::string line{};
        GroupData* currentGroup{ &inputData.Groups.emplace_back() };
        while (std::getline(inputStream, line))
        {
            if (line.empty())
            {
                currentGroup = &inputData.Groups.emplace_back();
                continue;
            }

            currentGroup->RawAnswers.emplace_back(std::move(line));
        }

        return true;
    }

    void ComputeOutput(const InputData& input, OutputData& output, const AoCContext& context)
    {
        std::vector<u64> groupAnswers(input.Groups.size());
        std::transform(input.Groups.begin(), input.Groups.end(), groupAnswers.begin(), Internal::AggregateGroupAnswers);
        output.SumGroupAnswerCount = std::accumulate(groupAnswers.begin(), groupAnswers.end(), 0ULL, [](u64 total, u64 value) { return total + Math::PopulationCount(value); });

        std::transform(input.Groups.begin(), input.Groups.end(), groupAnswers.begin(), Internal::AggregateCommonAnswers);
        output.SumCommonAnswerCount = std::accumulate(groupAnswers.begin(), groupAnswers.end(), 0ULL, [](u64 total, u64 value) { return total + Math::PopulationCount(value); });
    }

    bool ValidateTestOutput(const OutputData& output, const AoCContext& context)
    {
        bool didTestsPass{ true };

        didTestsPass &= output.SumGroupAnswerCount == 11;
        didTestsPass &= output.SumCommonAnswerCount == 6;

        return didTestsPass;
    }

    void PrintOutput(const OutputData& output)
    {
        fmt::print("Sum Group Answer Count: {}\n", output.SumGroupAnswerCount);
        fmt::print("Sum Common Answer Count: {}\n", output.SumCommonAnswerCount);
    }
}

void main()
{
    AoC::Run<AoC::InputData, AoC::OutputData>({ AoC::s_testInputData });
}