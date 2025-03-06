#ifndef LOGICCIRUIT_H
#define LOGICCIRUIT_H

#include "LogicGate.h"
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <cstdint>

class LogicCircuit
{
private:
    int _inputPinsCount;
    int _gatesCount;
    std::vector<std::vector<int>> _gatesiPin_list;

    std::vector<std::shared_ptr<LogicGate>> _gates;
    std::vector<std::shared_ptr<LogicGate>> _iPins;

public:
    bool loadFromFile(const std::string &filePath);

    const int getInputPinsCount()
    {
        return _inputPinsCount;
    }

    const int getOutputPinsCount();
    
    const int getGatesCount()
    {
        return _gatesCount;
    }

    std::vector<int8_t> simuulate(std::vector<int8_t> _iPins);
};

#endif // LOGICCIRUIT_H
