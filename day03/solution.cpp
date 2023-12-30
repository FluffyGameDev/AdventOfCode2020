#include "data.h"
#include "aoc.h"

namespace AoC
{
    namespace Internal
    {
        u64 ComputeTreeHitCount(const Grid<char>& grid, const Vector2S& direction)
        {
            u64 hitCount{};
            Vector2S position{};

            while (position.y < grid.Size.y)
            {
                if (grid.Data[grid.ComputeFlatIndex(position)] == '#')
                {
                    ++hitCount;
                }

                position += direction;
                position.x %= grid.Size.x;
            }

            return hitCount;
        }
    }

    bool ReadInput(std::istream& inputStream, InputData& inputData, const AoCContext& context)
    {
        std::string line{};
        while (std::getline(inputStream, line))
        {
            inputData.Map.Size.x = (s32)line.size();
            ++inputData.Map.Size.y;
            inputData.Map.Data.insert(inputData.Map.Data.end(), line.begin(), line.end());
        }
        return true;
    }

    void ComputeOutput(const InputData& input, OutputData& output, const AoCContext& context)
    {
        output.TestTreeHitCount = Internal::ComputeTreeHitCount(input.Map, { 3, 1 });

        output.TreeHitCountProduct = 1;
        const Vector2S testDirections[]
        {
            { 1, 1 },
            { 3, 1 },
            { 5, 1 },
            { 7, 1 },
            { 1, 2 }
        };
        for (const Vector2S& direction : testDirections)
        {
            output.TreeHitCountProduct *= Internal::ComputeTreeHitCount(input.Map, direction);
        }
    }

    bool ValidateTestOutput(const OutputData& output, const AoCContext& context)
    {
        bool didTestsPass{ true };

        didTestsPass &= output.TestTreeHitCount == 7;
        didTestsPass &= output.TreeHitCountProduct == 336;

        return didTestsPass;
    }

    void PrintOutput(const OutputData& output)
    {
        fmt::print("Tree Hit Count (3,1): {}\n", output.TestTreeHitCount);
        fmt::print("Tree Hit Count Product: {}\n", output.TreeHitCountProduct);
    }
}

void main()
{
    AoC::Run<AoC::InputData, AoC::OutputData>({ AoC::s_testInputData });
}