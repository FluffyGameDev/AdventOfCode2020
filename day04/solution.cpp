#include "data.h"
#include "aoc.h"

#include <numeric>
#include <set>
#include <string_view>
#include <unordered_map>

namespace AoC
{
    namespace Internal
    {
        struct PassportCounter
        {
            u64 ValidByEntriesCount{};
            u64 ValidByValuesCount{};
        };

        bool AreEntriesValid(const PassportData& passport)
        {
            static const std::set<std::string> mandatoryEntries{ "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };

            u64 mandatoryCount{};
            for (const PassportEntry& entry : passport.Entries)
            {
                if (mandatoryEntries.find(entry.EntryName) != mandatoryEntries.end())
                {
                    ++mandatoryCount;
                }
            }
            return mandatoryCount >= 7;
        }

        bool IsDigit(char c)
        {
            return std::isdigit(c);
        }

        bool IsHexa(char c)
        {
            return std::isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
        }

        bool IsValidYear(const std::string& value, u32 min, u32 max)
        {
            u32 year{ std::stoul(value) };
            return value.size() == 4 && year >= min && year <= max;
        }

        bool IsValidHeight(const std::string& value)
        {
            if (value.size() > 2)
            {
                u32 size{ std::stoul(value) };
                if (value[value.size() - 2] == 'c' && value[value.size() - 1] == 'm')
                {
                    return size >= 150 && size <= 193;
                }

                if (value[value.size() - 2] == 'i' && value[value.size() - 1] == 'n')
                {
                    return size >= 59 && size <= 76;
                }
            }

            return false;
        }

        bool IsValidColorHex(const std::string& value)
        {
            return value.size() == 7 && value[0] == '#' && std::all_of(value.begin() + 1, value.end(), IsHexa);
        }

        bool IsValidColorText(const std::string& value)
        {
            static const std::set<std::string> possibleColors{ "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
            return possibleColors.find(value) != possibleColors.end();
        }

        bool AreValuesValid(const PassportData& passport)
        {
            using EntryValidator = bool (*)(const std::string&);
            std::unordered_map<std::string, EntryValidator> validators
            {
                { "byr", [](const std::string& value) { return IsValidYear(value, 1920, 2002); } },
                { "iyr", [](const std::string& value) { return IsValidYear(value, 2010, 2020); } },
                { "eyr", [](const std::string& value) { return IsValidYear(value, 2020, 2030); } },
                { "hgt", [](const std::string& value) { return IsValidHeight(value); } },
                { "hcl", [](const std::string& value) { return IsValidColorHex(value); } },
                { "ecl", [](const std::string& value) { return IsValidColorText(value); } },
                { "pid", [](const std::string& value) { return value.size() == 9 && std::all_of(value.begin(), value.end(), IsDigit); } },
            };

            for (const PassportEntry& entry : passport.Entries)
            {
                const auto foundIt{  validators.find(entry.EntryName) };
                if (foundIt != validators.end() && !foundIt->second(entry.EntryValue))
                {
                    return false;
                }
            }

            return true;
        }

        PassportCounter* AccumulatePassportCounter(PassportCounter* current, const PassportData& passport)
        {
            if (AreEntriesValid(passport))
            {
                ++current->ValidByEntriesCount;

                if (AreValuesValid(passport))
                {
                    ++current->ValidByValuesCount;
                }
            }

            return current;
        }
    }

    bool ReadInput(std::istream& inputStream, InputData& inputData, const AoCContext& context)
    {
        std::string line{};
        std::string entry{};
        PassportData* currentPassport{ &inputData.Passports.emplace_back() };
        while (std::getline(inputStream, line))
        {
            if (line.empty())
            {
                currentPassport = &inputData.Passports.emplace_back();
                continue;
            }

            std::stringstream lineStream{ line };
            while (lineStream >> entry)
            {
                size_t separatorPosition{ entry.find_first_of(':') };
                PassportEntry& currentEntry{ currentPassport->Entries.emplace_back() };
                currentEntry.EntryName = entry.substr(0ULL, separatorPosition);
                currentEntry.EntryValue = entry.substr(separatorPosition + 1);
            }
        }
        return true;
    }

    void ComputeOutput(const InputData& input, OutputData& output, const AoCContext& context)
    {
        Internal::PassportCounter validCount{};
        auto* result{ std::accumulate(input.Passports.begin(), input.Passports.end(), &validCount, Internal::AccumulatePassportCounter) };

        output.PassportCorrectEntriesCount = validCount.ValidByEntriesCount;
        output.PassportCorrectValuesCount = validCount.ValidByValuesCount;
    }

    bool ValidateTestOutput(const OutputData& output, const AoCContext& context)
    {
        bool didTestsPass{ true };

        didTestsPass &= output.PassportCorrectEntriesCount == 8;
        didTestsPass &= output.PassportCorrectValuesCount == 4;

        return didTestsPass;
    }

    void PrintOutput(const OutputData& output)
    {
        fmt::print("Passports with correct entries: {}\n", output.PassportCorrectEntriesCount);
        fmt::print("Passports with correct values: {}\n", output.PassportCorrectValuesCount);
    }
}

void main()
{
    AoC::Run<AoC::InputData, AoC::OutputData>({ AoC::s_testInputData });
}