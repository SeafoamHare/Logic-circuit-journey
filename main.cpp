
#include "LogicGate.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

enum GateType
{
    AND = 1,
    OR = 2,
    NOT = 3
};

struct Connection
{
    int gateNumber;
    int pinNumber;
};

struct Gate
{
    GateType type;
    std::vector<Connection> inputs;
};

class LogicCircuit
{
private:
    int inputPinsCount;
    int gatesCount;
    std::vector<Gate> gates;

public:
    bool loadFromFile(const std::string &filePath)
    {
        std::ifstream file(filePath);

        // std::ifstream file("input.txt");
        if (!file.is_open())
        {
            std::cerr << "無法開啟檔案" << std::endl;
            return 1;
        }

        file >> inputPinsCount >> gatesCount;
        std::cout << inputPinsCount << std::endl;
        std::cout << gatesCount << std::endl;

        // std::vector<std::vector<double>> numbers(n);
        float flo;
        gates.resize(gatesCount);

        for (int i = 0; i < gatesCount; ++i)
        {
            int gateType;
            file >> gateType;
            gates[i].type = static_cast<GateType>(gateType);
            std::cout << "Type: " << gates[i].type << " ";
            float input;
            while (file >> input && input != 0)
            {
                // Connection conn;
                std::cout << input << " ";
                // if (input < 0) {
                //     conn.gateNumber = 0;  // 表示這是一個輸入引腳
                //     conn.pinNumber = -input;
                // } else {
                //     conn.gateNumber = input;
                //     file.ignore();  // 忽略小數點
                //     file >> conn.pinNumber;
                // }
                // gates[i].inputs.push_back(conn);
            }
            std::cout<<" "<<std::endl;
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
        default:
            std::cout << "Invalid command. Please try again.\n";
        }
    }

    return 0;
}