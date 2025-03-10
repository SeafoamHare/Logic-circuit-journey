#ifndef LOGICCIRUITCONTROLLER_H
#define LOGICCIRUITCONTROLLER_H

#include "TextUI.h"
#include "LogicCircuit.h"
#include "LogicGate.h"

class LogicCircuitController
{
private:
    LogicCircuit _circuit;
    TextUI _textui;
    
public:
    
    void run_Application();

    bool loadCircuit();

    void runSimulation();

    void generateInputCombinations();
};

#endif // LOGICCIRUITCONTROLLER_H