#include "../inc/LogicCircuit.h"
#include <fstream>
#include <unordered_set>

const int LogicCircuit::getOutputPinsCount()
{
    std::unordered_set<int> seenNumbers;

    for (const auto &row : gatesiPin_list)
    {
        for (size_t i = 0; i < row.size(); i++)
        {
            seenNumbers.insert(row[i]);
        }
    }

    int count = 0;
    for (int i = 1; i <= gatesCount; i++)
    {
        if (seenNumbers.find(i) == seenNumbers.end())
        {
            count++;
        }
    }

    return count;
}

bool LogicCircuit::loadFromFile(const std::string &filePath)
{
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        std::cerr << "無法開啟檔案" << std::endl;
        return false;
    }
    file >> inputPinsCount >> gatesCount;

    // Initialize iPins
    _iPins.clear();
    _iPins.resize(inputPinsCount);
    for (int i = 0; i < inputPinsCount; i++)
    {
        _iPins[i] = std::make_shared<InputPin>();
    }

    // Initialize gates
    gates.clear();
    gates.resize(gatesCount);
    gatesiPin_list.clear();
    gatesiPin_list.resize(gatesCount);
    for (int i = 0; i < gatesCount; i++)
    {
        int gateType;
        file >> gateType;
        std::vector<int> inputs;
        float input;
        while (file >> input && input != 0)
        {
            int ii = (int)input;
            gatesiPin_list[i].push_back(ii);
        }
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

        if (newGate)
        {
            gates[i] = newGate;
        }
    }
    for (int i = 0; i < gatesCount; i++)
    {
        for (auto ipin : gatesiPin_list[i])
        {
            if (ipin < 0)
            {
                gates[i]->addInputPin(_iPins[-ipin - 1]);
            }
            else
            {
                gates[i]->addInputPin(gates[ipin - 1]);
            }
        }
    }

    file.close();
    return true;
}

std::vector<int8_t> LogicCircuit::simuulate(std::vector<int8_t> iPins)
{
    for (int i = 0; i < inputPinsCount; i++)
    {
        _iPins[i]->addInputPin(iPins[i]);
    }

    bool undone = true;
    while (undone)
    {
        undone = false;
        for (int i = 0; i < gatesCount; i++)
        {
            if (gates[i]->getOutput() == UNINITIALIZED)
            {
                undone = true;
                gates[i]->compute();
            }
        }
    }

    std::vector<int8_t> opins;
    for (auto gate : gates)
    {
        if (gate.use_count() == 2)
        {
            opins.push_back(gate->getOutput());
        }
    }

    for (int i = 0; i < gatesCount; i++)
    {
        gates[i]->reset();
    }
    return opins;
}
