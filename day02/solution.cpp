#include "data.h"
#include "aoc.h"

namespace AoC
{
    namespace Internal
    {
        bool IsPasswordValid(const PasswordData& passwordData)
        {
            u64 charCount{ (u64)std::count(passwordData.Password.begin(), passwordData.Password.end(), passwordData.ExpectedChar) };
            return passwordData.ExpectedCount.IsInRange(charCount);
        }

        bool IsPasswordValidNewRules(const PasswordData& passwordData)
        {
            bool doesFirstPositionMatch{ passwordData.Password[passwordData.ExpectedCount.Min - 1] == passwordData.ExpectedChar };
            bool doesSecondPositionMatch{ passwordData.Password[passwordData.ExpectedCount.Max - 1] == passwordData.ExpectedChar };
            return doesFirstPositionMatch ^ doesSecondPositionMatch;
        }
    }

    bool ReadInput(std::istream& inputStream, InputData& inputData, const AoCContext& context)
    {
        std::string line{};
        while (std::getline(inputStream, line))
        {
            std::stringstream lineStream{ line };
            PasswordData& newEntry{ inputData.PasswordsData.emplace_back() };

            lineStream >> newEntry.ExpectedCount.Min;
            lineStream.seekg(1, lineStream.cur);
            lineStream >> newEntry.ExpectedCount.Max;
            lineStream.seekg(1, lineStream.cur);
            lineStream >> newEntry.ExpectedChar;
            lineStream.seekg(2, lineStream.cur);
            lineStream >> newEntry.Password;
        }

        return true;
    }

    void ComputeOutput(const InputData& input, OutputData& output, const AoCContext& context)
    {
        output.ValidPasswordCount = (u64)std::count_if(input.PasswordsData.begin(), input.PasswordsData.end(), Internal::IsPasswordValid);
        output.ValidPasswordCountNewRules = (u64)std::count_if(input.PasswordsData.begin(), input.PasswordsData.end(), Internal::IsPasswordValidNewRules);
    }

    bool ValidateTestOutput(const OutputData& output, const AoCContext& context)
    {
        bool didTestsPass{ true };

        didTestsPass &= output.ValidPasswordCount == 2;
        didTestsPass &= output.ValidPasswordCountNewRules == 1;

        return didTestsPass;
    }

    void PrintOutput(const OutputData& output)
    {
        fmt::print("Valid Password Count: {}\n", output.ValidPasswordCount);
        fmt::print("Valid Password Count (new rules): {}\n", output.ValidPasswordCountNewRules);
    }
}

void main()
{
    AoC::Run<AoC::InputData, AoC::OutputData>({ AoC::s_testInputData });
}