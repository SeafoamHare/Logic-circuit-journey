#ifndef LOGICGATE_H
#define LOGICGATE_H

#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <cstdint>

const int8_t UNINITIALIZED = -1;
class LogicGate
{
public:
    LogicGate();
    virtual ~LogicGate() = default;
    int8_t getOutput();
    void reset();

    /// @overload
    /// @brief LogicGet for And, Or, Not
    void addInputPin(std::shared_ptr<LogicGate> pin);
    /// @brief for InputPin
    void addInputPin(int8_t pin);

    virtual void compute() = 0;

protected:
    std::vector<std::shared_ptr<LogicGate>> ipin_vector_;
    int8_t output_ = UNINITIALIZED;
};

class AndGate : public LogicGate
{
public:
    void compute() override;
};

class OrGate : public LogicGate
{
public:
    void compute() override;
};

class NotGate : public LogicGate
{
public:
    void compute() override;
};

class InputPin : public LogicGate
{
public:
    void compute() override;
};

#endif // LOGICGATE_H
