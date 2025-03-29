#include <iostream>
#include <map>
#include <vector>
#include <bitset>
#include <array>
#include <cpp-dump.hpp>

using IndexT = std::bitset<9>;
using OffsetT = std::bitset<12>;

// 5 layers of address tables create tree-like structure
using PTE = std::unordered_map<IndexT, std::vector<OffsetT>>;
using PMD = std::unordered_map<IndexT, PTE>;
using PUD = std::unordered_map<IndexT, PMD>;
using P4D = std::unordered_map<IndexT, PUD>;
using PGD = std::unordered_map<IndexT, P4D>;

namespace cp = cpp_dump;

CPP_DUMP_DEFINE_EXPORT_OBJECT_GENERIC(VPN, Offset);
struct PageAddress
{
    std::array<IndexT, 5> VPN; // virtual page number
    OffsetT Offset;
};

int main()
{
    std::vector<PageAddress> InputData;
    InputData.push_back({{134, 0, 0, 0, 0}, 123});
    InputData.push_back({{0, 0, 0, 0, 0}, 234});
    InputData.push_back({{0, 0, 0, 0, 0}, 452});
    InputData.push_back({{0, 0, 0, 0, 34}, 432});
    InputData.push_back({{0, 0, 0, 0, 10}, 634});
    InputData.push_back({{0, 0, 0, 12, 343}, 9976});

    PGD Result;
    for (const auto& Data : InputData)
    {
        Result[Data.VPN[0]][Data.VPN[1]][Data.VPN[2]][Data.VPN[3]][Data.VPN[4]].push_back(Data.Offset);
    }

    CPP_DUMP_SET_OPTION(max_depth, 10);
    cpp_dump(Result | cp::bin());
}
