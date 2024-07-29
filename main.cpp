
#include "LogicGate.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

class LogicCircuit
{
private:
    int inputPinsCount;
    int gatesCount;
    std::vector<std::shared_ptr<LogicGate>> gates;
    std::vector<std::shared_ptr<LogicGate>> _iPins;

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
        // std::cout << inputPinsCount << std::endl;
        // std::cout << gatesCount << std::endl;

        // Initialize iPins
        _iPins.resize(inputPinsCount);
        for (int i = 0; i < inputPinsCount; i++)
        {
            _iPins[i] = std::make_shared<InputPin>();
        }

        // Initialize gates with nullptr or default gate
        gates.resize(gatesCount);

        std::vector<std::vector<int>> gatesiPin_list(gatesCount);
        for (int i = 0; i < gatesCount; i++)
        {
            int gateType;
            file >> gateType;
            // std::cout << "Type: " << gateType << std::endl;
            std::vector<int> inputs;
            float input;
            while (file >> input && input != 0)
            {
                int ii = (int)input;
                // std::cout << ii << " ";
                gatesiPin_list[i].push_back(ii);
                
            }
            // std::cout<<" "<<std::endl;
            std::shared_ptr<LogicGate> newGate;
            switch (gateType)
            {
            case 1:
                newGate = std::make_shared<AndGate>();
                break;
            case 2:
                newGate = std::make_shared<OrGate>();
                break;
            case 3:
                newGate = std::make_shared<NotGate>();
                break;
            
            default:
                break;
            }

            if(newGate)
            {
                gates[i] = newGate;
            }
            // std::cout<<gates[i]<<std::endl;
        }

        for(int i=0; i<gatesCount; i++){
            for(auto ipin: gatesiPin_list[i])
            {
                if(ipin < 0)
                {
                    gates[i]->addInputPin(_iPins[-ipin-1]);
                }else
                {
                    gates[i]->addInputPin(gates[ipin-1]);
                }
                
            }
        }

        file.close();
        return true;
    }
    
    const int get_inputPinsCount(){
        return inputPinsCount;
    }

    const int get_gatesCount(){
        return gatesCount;
    }

    // void printCircuitInfo()
    // {
    //     std::cout << "Circuit: " << inputPinsCount << " input pins, 1 output pin and "
    //               << gatesCount << " gates\n";
    // }

    std::vector<int8_t> simuulate(std::vector<int8_t> iPins)
    {
        // std::cout<<"Simuulate"<<std::endl;
        for(int i=0; i<inputPinsCount; i++)
        {
            _iPins[i]->addInputPin(iPins[i]);
        }

       
        bool undone = true;
        while(undone){
            undone = false;
            for(int i=0; i<gatesCount; i++)
            {
                // std::cout<<"point: "<<gates[i]<<" ";
                if(gates[i]->getOutput()==UNINITIALIZED){
                    undone=true;
                    gates[i]->compute();
                }
                // std::cout<<"oup; "<<static_cast<int>(gates[i]->getOutput())<<std::endl;
            }
            // std::cout<<"------ " <<std::endl;
        }

        std::vector<int8_t> opins;
        for(auto gate : gates){
            if(gate.use_count() == 2){
                opins.push_back(gate->getOutput());
            }
        }

        for(int i=0; i<gatesCount; i++)
        {
            gates[i]->reset();
        }
        return opins;
    }
};


void displayMenu()
{
    std::cout << "1. Load logic circuit file\n";
    std::cout << "2. Simulation\n";
    std::cout << "3. Display truth table\n";
    std::cout << "4. Exit\n";
    std::cout << "5. Test.\n";
    std::cout << "Command: ";
}

// 打印分隔線
void printSeparator(int length) {
    for (int i = 0; i < length; ++i) {
        std::cout << "-";
    }
    std::cout << "+" << "--" << std::endl;
}

void printSRheader(size_t i_size, size_t o_size){
    for (size_t i = 0; i < i_size; ++i) {
        std::cout << "i";
    }
    std::cout << "|" ;
    for (size_t i = 0; i < o_size; ++i) {
        std::cout << "o";
    }
    std::cout  <<  std::endl;
    // 打印矢量索引
    for (size_t i = 0; i < i_size; ++i) {
        std::cout << i + 1;
    }
    std::cout << "|";

    for (size_t i = 0; i < o_size; ++i) {
        std::cout << i + 1;
    }
    std::cout  <<  std::endl;
    // 打印分隔線
    printSeparator(i_size + 2);
}
// 顯示模擬結果
void displaySimulationResult(const std::vector<int8_t>& ipins, const std::vector<int8_t>& opins) {
    // 打印 ipins
    for (auto val : ipins) {
        std::cout << static_cast<int>(val);
    }
    std::cout << "|";

    // 打印 outps
    for (auto val : opins) {
        std::cout << static_cast<int>(val);
    }

    std::cout  <<  std::endl;
}
LogicCircuit circuit;
class TextUI{    

public:
    bool loadCircuit()
    {
        std::string filePath;
        std::cout << "Please key in a file path: ";
        std::cin >> filePath;

        if (circuit.loadFromFile(filePath))
        {
            std::cout << "Circuit Load down\n";
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
        std::vector<int8_t> ipins(circuit.get_gatesCount());
        for (int i = 0; i < circuit.get_gatesCount(); ++i)
        {
            int in;
            do
            {
                std::cout << "Please key in the value of input pin " << i + 1 << ": ";
                std::cin >> in;
                if (in != 0 && in != 1)
                {
                    std::cout << "The value of input pin must be 0/1" << ipins[i] << std::endl;
                }
            } while (in != 0 && in != 1);
            ipins[i] = in;
        }
        std::vector<int8_t> outps = circuit.simuulate(ipins);
        std::cout << "Simulation Result:" << std::endl;
        // 打印
        printSRheader(ipins.size(), outps.size());
        displaySimulationResult(ipins, outps);
    }

    void generateInputCombinations()
    {
        int totalCombinations = std::pow(2, circuit.get_inputPinsCount());
        std::cout << "TruthTable Result:" << std::endl;
        for (int i = 0; i < totalCombinations; ++i)
        {
            std::vector<int8_t> ipins(circuit.get_inputPinsCount());
            for (int j = 0; j < circuit.get_inputPinsCount(); ++j)
            {
                int8_t ip = (i >> j) & 1;
                ipins[circuit.get_inputPinsCount() - j - 1] = ip;
            }
            // for(auto a: ipins){
            //     std::cout<<static_cast<int>(a)<<" ";
            // }
            // std::cout<<"done comb------ "<<std::endl;

            std::vector<int8_t> outps = circuit.simuulate(ipins);
            if (i == 0)
            {
                // 打印頭部
                printSRheader(ipins.size(), outps.size());
            }

            displaySimulationResult(ipins, outps);
        }
    }
};

int main()
{
    TextUI textui;
    int command;
    bool circuitLoaded = false;

    while (true)
    {
        displayMenu();
        std::cin >> command;

        switch (command)
        {
        case 1:
            circuitLoaded = textui.loadCircuit();
            break;
        case 2:
            if (circuitLoaded)
            {
                textui.runSimulation();
            }
            else
            {
                std::cout << "Please load an lcf file, before using this operation.\n";
            }
            break;
        case 3:
            if (circuitLoaded)
            {
                textui.generateInputCombinations();
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
            textui.runSimulation();
            break;
        default:
            std::cout << "Invalid command. Please try again.\n";
            
        }
    }

    return 0;
}