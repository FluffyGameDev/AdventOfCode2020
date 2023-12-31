#include "data.h"
#include "aoc.h"

#include <numeric>

namespace AoC
{
    namespace Internal
    {
        u64 ComputeSeatId(const std::string& pass)
        {
            u64 row{};
            u64 column{};

            for (char c : pass)
            {
                switch (c)
                {
                    case 'F': { row = (row << 1); break; }
                    case 'B': { row = (row << 1) | 1; break; }
                    case 'L': { column = (column << 1); break; }
                    case 'R': { column = (column << 1) | 1; break; }
                }
            }

            return row * 8 + column;
        }

        RangeU64* ReduceRange(RangeU64* range, u64 value)
        {
            range->Min = std::min(range->Min, value);
            range->Max = std::max(range->Max, value);
            return range;
        }
    }

    bool ReadInput(std::istream& inputStream, InputData& inputData, const AoCContext& context)
    {
        std::string line{};
        while (inputStream >> line)
        {
            inputData.BoardingPasses.emplace_back(std::move(line));
        }
        return true;
    }

    void ComputeOutput(const InputData& input, OutputData& output, const AoCContext& context)
    {
        std::vector<u64> seatIds{};
        seatIds.resize(input.BoardingPasses.size());
        std::transform(input.BoardingPasses.begin(), input.BoardingPasses.end(), seatIds.begin(), Internal::ComputeSeatId);

        RangeU64 seatIdRange{ seatIds[0], seatIds[0] };
        output.SeatIdRange = *std::accumulate(seatIds.begin(), seatIds.end(), &seatIdRange, Internal::ReduceRange);

        u64 maxSeatId{ Internal::ComputeSeatId("BBBBBBBRRR") };
        for (u64 i = 0; i < seatIdRange.Min; ++i) { output.MissingSeatId ^= i; }
        for (u64 i = seatIdRange.Max + 1; i <= maxSeatId; ++i) { output.MissingSeatId ^= i; }
        output.MissingSeatId = std::accumulate(seatIds.begin(), seatIds.end(), output.MissingSeatId, [](u64 lhs, u64 rhs) { return lhs ^ rhs; });
    }

    bool ValidateTestOutput(const OutputData& output, const AoCContext& context)
    {
        bool didTestsPass{ true };

        didTestsPass &= output.SeatIdRange.Max == 820;

        return didTestsPass;
    }

    void PrintOutput(const OutputData& output)
    {
        fmt::print("Seat Id range: [{},{}]\n", output.SeatIdRange.Min, output.SeatIdRange.Max);
        fmt::print("Missing Seat Id: {}\n", output.MissingSeatId);
    }
}

void main()
{
    AoC::Run<AoC::InputData, AoC::OutputData>({ AoC::s_testInputData });
}