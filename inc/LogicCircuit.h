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
    int inputPinsCount;
    int gatesCount;
    std::vector<std::vector<int>> gatesiPin_list;

    std::vector<std::shared_ptr<LogicGate>> gates;
    std::vector<std::shared_ptr<LogicGate>> _iPins;

public:
    bool loadFromFile(const std::string &filePath);

    const int getInputPinsCount()
    {
        return inputPinsCount;
    }

    const int getOutputPinsCount();
    
    const int getGatesCount()
    {
        return gatesCount;
    }

    std::vector<int8_t> simuulate(std::vector<int8_t> iPins);
};

#endif // LOGICCIRUIT_H
