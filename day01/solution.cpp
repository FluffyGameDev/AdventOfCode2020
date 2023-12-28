#include "data.h"
#include "aoc.h"

namespace AoC
{
    bool ReadInput(std::istream& inputStream, InputData& inputData, const AoCContext& context)
    {
        u64 number{};
        while (inputStream >> number)
        {
            inputData.Numbers.push_back(number);
        }
        return true;
    }

    void ComputeOutput(const InputData& input, OutputData& output, const AoCContext& context)
    {
        bool foundResult{};
        for (size_t i = 0; i < input.Numbers.size() - 1; ++i)
        {
            u64 x{ input.Numbers[i] };
            for (size_t j = i + 1; j < input.Numbers.size(); ++j)
            {
                u64 y{ input.Numbers[j] };
                if (x + y == 2020)
                {
                    output.TwoNumbersProduct = x * y;
                    foundResult = true;
                    break;
                }
            }

            if (foundResult)
            {
                break;
            }
        }

        foundResult = false;
        for (size_t i = 0; i < input.Numbers.size() - 2; ++i)
        {
            u64 x{ input.Numbers[i] };
            for (size_t j = i + 1; j < input.Numbers.size() - 1; ++j)
            {
                u64 y{ input.Numbers[j] };
                for (size_t k = j + 1; k < input.Numbers.size(); ++k)
                {
                    u64 z{ input.Numbers[k] };
                    if (x + y + z == 2020)
                    {
                        output.ThreeNumbersProduct = x * y * z;
                        foundResult = true;
                        break;
                    }
                }

                if (foundResult)
                {
                    break;
                }
            }

            if (foundResult)
            {
                break;
            }
        }
    }

    bool ValidateTestOutput(const OutputData& output, const AoCContext& context)
    {
        bool didTestsPass{ true };

        didTestsPass &= output.TwoNumbersProduct == 514579;
        didTestsPass &= output.ThreeNumbersProduct == 241861950;

        return didTestsPass;
    }

    void PrintOutput(const OutputData& output)
    {
        fmt::print("2 Numbers product: {}\n", output.TwoNumbersProduct);
        fmt::print("3 Numbers product: {}\n", output.ThreeNumbersProduct);
    }
}

void main()
{
    AoC::Run<AoC::InputData, AoC::OutputData>({ AoC::s_testInputData });
}