
#include "LogicGate.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>


class LogicCircuit
{
private:
    int inputPinsCount;
    int gatesCount;
    std::vector<std::shared_ptr<LogicGate>> gates;
    std::vector<std::shared_ptr<LogicGate>> iPins;
    std::vector<std::shared_ptr<LogicGate>> oPins;

public:
    bool loadFromFile(const std::string &filePath)
    {
        std::ifstream file(filePath);

        if (!file.is_open())
        {
            std::cerr << "無法開啟檔案" << std::endl;
            return false;
        }
        file >> inputPinsCount >> gatesCount;
        std::cout << inputPinsCount << std::endl;
        std::cout << gatesCount << std::endl;

        // Initialize iPins
        iPins.resize(inputPinsCount);
        // for (int i = 0; i < inputPinsCount; ++i)
        // {
        //     iPins[i] = nullptr; // Or gates[i] = std::make_shared<DefaultLogicGate>();
        // }

        // Initialize gates with nullptr or default gate
        gates.resize(gatesCount);
        // for (int i = 0; i < gatesCount; ++i)
        // {
        //     gates[i] = nullptr; // Or gates[i] = std::make_shared<DefaultLogicGate>();
        // }
    
        for (int i = 0; i < gatesCount; ++i)
        {
            int gateType;
            file >> gateType;
            std::cout << "Type: " << gateType << std::endl;
            std::vector<int> inputs;
            std::vector<std::shared_ptr<LogicGate>> selecteGates;
            float input;
            while (file >> input && input != 0)
            {
                int ii = (int)input;
                std::cout << ii << " ";
                if(input < 0){
                    selecteGates.push_back(iPins[-ii-1]);
                }else{
                    selecteGates.push_back(gates[input-1]);
                }
                
            }
            std::cout<<" "<<std::endl;

            std::shared_ptr<LogicGate> newGate;
            switch (gateType)
            {
            case 1:
                newGate = std::make_shared<AndGate>(selecteGates);
                break;
            case 2:
                newGate = std::make_shared<OrGate>(selecteGates);
                break;
            case 3:
                newGate = std::make_shared<NotGate>(selecteGates);
                break;
            
            default:
                break;
            }

            if(newGate)
            {
                gates[i] = newGate;
            }
        }

        file.close();
        return true;
    }

    void printCircuitInfo()
    {
        std::cout << "Circuit: " << inputPinsCount << " input pins, 1 output pin and "
                  << gatesCount << " gates\n";
    }

    // 其他方法如 simulate 和 displayTruthTable 將在這裡實現
};

LogicCircuit circuit;

void displayMenu()
{
    std::cout << "1. Load logic circuit file\n";
    std::cout << "2. Simulation\n";
    std::cout << "3. Display truth table\n";
    std::cout << "4. Exit\n";
    std::cout << "Command: ";
}

bool loadCircuit()
{
    std::string filePath;
    std::cout << "Please key in a file path: ";
    std::cin >> filePath;

    if (circuit.loadFromFile(filePath))
    {
        std::cout << "Circuit: [Details about the loaded circuit]\n";
        return true;
    }
    else
    {
        std::cout << "File not found or file format error!!\n";
        return false;
    }
}

void runSimulation()
{
    // 實現模擬邏輯
}

int main()
{
    int command;
    bool circuitLoaded = false;

    while (true)
    {
        displayMenu();
        std::cin >> command;

        switch (command)
        {
        case 1:
            circuitLoaded = loadCircuit();
            break;
        case 2:
            if (circuitLoaded)
            {
                // runSimulation();
            }
            else
            {
                std::cout << "Please load an lcf file, before using this operation.\n";
            }
            break;
        case 3:
            if (circuitLoaded)
            {
                // circuit.displayTruthTable();
            }
            else
            {
                std::cout << "Please load an lcf file, before using this operation.\n";
            }
            break;
        case 4:
            std::cout << "Goodbye, thanks for using LS.\n";
            return 0;
        case 5:
            std::cout << "Test.\n";
            circuit.loadFromFile("File1.lcf");
        default:
            std::cout << "Invalid command. Please try again.\n";
            
        }
    }

    return 0;
}