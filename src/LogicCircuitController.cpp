#include "../inc/TextUI.h"
#include "../inc/LogicCircuitController.h"
#include <algorithm>
#include <cmath>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

void LogicCircuitController::run_Application()
{
    int command;
    bool circuitLoaded = false;
    std::string input;

    while (true)
    {
        textui.displayMenu();
        std::getline(std::cin, input);

        // 去除前後空白
        input.erase(0, input.find_first_not_of(" \t"));
        input.erase(input.find_last_not_of(" \t") + 1);

        std::istringstream iss(input);

        if (iss >> command && iss.eof())
        {
            switch (command)
            {
            case 1:
                circuitLoaded = loadCircuit();
                break;
            case 2:
                if (circuitLoaded)
                {
                    runSimulation();
                }
                else
                {
                    std::cout << "Please load an lcf file, before using this operation." << std::endl;
                }
                break;
            case 3:
                if (circuitLoaded)
                {
                    generateInputCombinations();
                }
                else
                {
                    std::cout << "Please load an lcf file, before using this operation." << std::endl;
                }
                break;
            case 4:
                std::cout << "Goodbye, thanks for using LS." << std::endl;
                return;
            default:
                std::cout << "Invalid command. Please try again." << std::endl;
            }
        }
        else
        {
            std::cout << "Invalid input. Please enter a single number." << std::endl;
        }
    }
}

bool LogicCircuitController::loadCircuit()
{
    std::string filePath;
    std::cout << "Please key in a file path: ";
    std::getline(std::cin >> std::ws, filePath);

    // 去除前後空白
    filePath.erase(0, filePath.find_first_not_of(" \t"));
    filePath.erase(filePath.find_last_not_of(" \t") + 1);

    if (filePath.empty())
    {
        std::cout << "Invalid input. File path cannot be empty." << std::endl;
        return false;
    }

    if (circuit.loadFromFile(filePath))
    {
        textui.displayCircuitLoadedResult(circuit.getInputPinsCount(),
                                          circuit.getOutputPinsCount(),
                                          circuit.getGatesCount());
        return true;
    }
    else
    {
        std::cout << "File not found or file format error!!" << std::endl;
        return false;
    }
}

void LogicCircuitController::runSimulation()
{
    std::vector<int8_t> ipins(circuit.getInputPinsCount());
    for (int i = 0; i < circuit.getInputPinsCount(); i++)
    {
        int in;
        std::string input;
        do
        {
            std::cout << "Please key in the value of input pin " << i + 1 << ": ";
            std::getline(std::cin, input);

            // 去除前後的空白字符
            input.erase(0, input.find_first_not_of(" \t"));
            input.erase(input.find_last_not_of(" \t") + 1);

            if (input.empty())
            {
                std::cout << "Invalid input. Please enter a number (0 or 1)." << std::endl;
                continue;
            }

            std::istringstream iss(input);
            if (iss >> in && iss.eof()) // 確保整個字符串都被轉換為數字
            {
                if (in == 0 || in == 1)
                {
                    break; // 有效輸入，退出循環
                }
                else
                {
                    std::cout << "The value of input pin must be 0 or 1" << std::endl;
                }
            }
            else
            {
                std::cout << "Invalid input. Please enter only one number (0 or 1)." << std::endl;
            }
        } while (true);
        ipins[i] = in;
    }
    std::vector<int8_t> outps = circuit.simuulate(ipins);
    std::cout << "Simulation Result:" << std::endl;
    // 打印
    textui.printSRheader(ipins.size(), outps.size());
    textui.displaySimulationResult(ipins, outps);
}

void LogicCircuitController::generateInputCombinations()
{
    int totalCombinations = std::pow(2, circuit.getInputPinsCount());
    std::cout << "TruthTable Result:" << std::endl;
    for (int i = 0; i < totalCombinations; ++i)
    {
        std::vector<int8_t> ipins(circuit.getInputPinsCount());
        for (int j = 0; j < circuit.getInputPinsCount(); ++j)
        {
            int8_t ip = (i >> j) & 1;
            ipins[circuit.getInputPinsCount() - j - 1] = ip;
        }

        std::vector<int8_t> outps = circuit.simuulate(ipins);
        if (i == 0)
        {
            // 打印頭部
            textui.printSRheader(ipins.size(), outps.size());
        }

        textui.displaySimulationResult(ipins, outps);
    }
}
