#include "../inc/LogicCircuit.h"
#include <fstream>
#include <unordered_set>

const int LogicCircuit::getOutputPinsCount()
{
    std::unordered_set<int> seenNumbers;

    for (const auto &row : _gatesiPin_list)
    {
        for (size_t i = 0; i < row.size(); i++)
        {
            seenNumbers.insert(row[i]);
        }
    }

    int count = 0;
    for (int i = 1; i <= _gatesCount; i++)
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
        std::cerr << "Cannot open the file." << std::endl;
        return false;
    }
    file >> _inputPinsCount >> _gatesCount;

    // Initialize iPins
    _iPins.clear();
    _iPins.resize(_inputPinsCount);
    for (int i = 0; i < _inputPinsCount; i++)
    {
        _iPins[i] = std::make_shared<InputPin>();
    }

    // Initialize gates
    _gates.clear();
    _gates.resize(_gatesCount);
    _gatesiPin_list.clear();
    _gatesiPin_list.resize(_gatesCount);
    for (int i = 0; i < _gatesCount; i++)
    {
        int gateType;
        file >> gateType;
        std::vector<int> inputs;
        float input;
        while (file >> input && input != 0)
        {
            int ii = (int)input;
            _gatesiPin_list[i].push_back(ii);
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
            _gates[i] = newGate;
        }
    }
    for (int i = 0; i < _gatesCount; i++)
    {
        for (auto ipin : _gatesiPin_list[i])
        {
            if (ipin < 0)
            {
                _gates[i]->addInputPin(_iPins[-ipin - 1]);
            }
            else
            {
                _gates[i]->addInputPin(_gates[ipin - 1]);
            }
        }
    }

    file.close();
    return true;
}

std::vector<int8_t> LogicCircuit::simuulate(std::vector<int8_t> iPins)
{
    for (int i = 0; i < _inputPinsCount; i++)
    {
        _iPins[i]->addInputPin(iPins[i]);
    }

    bool undone = true;
    while (undone)
    {
        undone = false;
        for (int i = 0; i < _gatesCount; i++)
        {
            if (_gates[i]->getOutput() == UNINITIALIZED)
            {
                undone = true;
                _gates[i]->compute();
            }
        }
    }

    std::vector<int8_t> opins;
    for (auto gate : _gates)
    {
        if (gate.use_count() == 2)
        {
            opins.push_back(gate->getOutput());
        }
    }

    for (int i = 0; i < _gatesCount; i++)
    {
        _gates[i]->reset();
    }
    return opins;
}
