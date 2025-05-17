#include <iostream>
#include <map>
#include <vector>
#include <bitset>
#include <array>
#include <cpp-dump.hpp>

using IndexT = uint16_t;
using OffsetT = uint32_t;

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
    OffsetT Offset; // offset in that page
};

int main()
{
    std::vector<PageAddress> InputData;

    unsigned long long VirtualAddress;
    unsigned long long PhysicalAddress;
    std::string CurrentLine;

    while (std::getline(std::cin, CurrentLine).good())
    {
        sscanf(CurrentLine.c_str(), "%llx : pfn %llx", &VirtualAddress, &PhysicalAddress);

        // std::cout << "VirtualAddress: " << std::hex << VirtualAddress << std::endl;
        // std::cout << "PhysicalAddress: " << std::hex << PhysicalAddress << std::endl;

        IndexT VPN0 = (VirtualAddress >> 51) & 0x1ff;
        IndexT VPN1 = (VirtualAddress >> 39) & 0x1ff;
        IndexT VPN2 = (VirtualAddress >> 30) & 0x1ff;
        IndexT VPN3 = (VirtualAddress >> 21) & 0x1ff;
        IndexT VPN4 = (VirtualAddress >> 12) & 0x1ff;
        OffsetT Offset = VirtualAddress & 0xfff;

        InputData.push_back({{VPN0, VPN1, VPN2, VPN3, VPN4}, Offset});
    }

    cpp_dump(InputData | cp::hex());

    PGD Result;
    for (const auto& Data : InputData)
    {
        Result[Data.VPN[0]][Data.VPN[1]][Data.VPN[2]][Data.VPN[3]][Data.VPN[4]].push_back(Data.Offset);
    }

    CPP_DUMP_SET_OPTION(max_depth, 10);
    CPP_DUMP_SET_OPTION(max_iteration_count, 256);
    cpp_dump(Result | cp::hex());
}
