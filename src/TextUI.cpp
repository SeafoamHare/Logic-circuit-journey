#include "../inc/TextUI.h"
#include <algorithm>
#include <cmath>
#include <sstream>
void TextUI::printSRheader(size_t i_size, size_t o_size)
{
    for (size_t i = 0; i < i_size; ++i)
    {
        std::cout << "i";
    }
    std::cout << "|";
    for (size_t i = 0; i < o_size; ++i)
    {
        std::cout << "o";
    }
    std::cout << std::endl;
    // 打印矢量索引
    for (size_t i = 0; i < i_size; ++i)
    {
        std::cout << i + 1;
    }
    std::cout << "|";

    for (size_t i = 0; i < o_size; ++i)
    {
        std::cout << i + 1;
    }
    std::cout << std::endl;
    // 打印分隔線
    printSeparator(i_size + 2);
}

void TextUI::displayCircuitLoadedResult(size_t ipCount, size_t opCount, size_t gateCount)
{
    std::cout << "Circuit Loaded successfully" << std::endl;
    std::cout << "Circuit : "
              << ipCount << " input pins, "
              << opCount << " output pins and "
              << gateCount << " gates" << std::endl;
}

// 顯示模擬結果
void TextUI::displaySimulationResult(const std::vector<int8_t> &ipins, const std::vector<int8_t> &opins)
{
    // 打印 ipins
    for (const auto &val : ipins)
    {
        std::cout << static_cast<int>(val);
    }
    std::cout << "|";

    // 打印 outps
    for (const auto &val : opins)
    {
        std::cout << static_cast<int>(val);
    }

    std::cout << std::endl;
}

// 打印分隔線
void TextUI::printSeparator(size_t length)
{
    for (size_t i = 0; i < length; ++i)
    {
        std::cout << "-";
    }
    std::cout << "+" << "--" << std::endl;
}
