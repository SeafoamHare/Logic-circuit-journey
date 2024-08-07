#ifndef TEXTUI_H
#define TEXTUI_H

#include "LogicCircuit.h"
#include "LogicGate.h"
#include <iostream>
#include <vector>
#include <string>

class TextUI
{
private:
public:
    void displayMenu()
    {
        std::cout << "1. Load logic circuit file\n";
        std::cout << "2. Simulation\n";
        std::cout << "3. Display truth table\n";
        std::cout << "4. Exit\n";
        std::cout << "Command: ";
    }

    // 打印分隔線
    void printSeparator(size_t length);

    void printSRheader(size_t i_size, size_t o_size);
    // 顯示載入結果
    void displayCircuitLoadedResult(size_t ipCount, size_t opCount, size_t gateCount);
    // 顯示模擬結果
    void displaySimulationResult(const std::vector<int8_t> &ipins, const std::vector<int8_t> &opins);
};

#endif // TEXTUI_H