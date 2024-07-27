#ifndef LOGICGATE_H
#define LOGICGATE_H

#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <cstdint>

class LogicGate {
public:
    LogicGate();
    virtual ~LogicGate() = default;
    bool isHaveAlliPinValue() const;
    int8_t getOutput();

    /// @overload
    /// @brief LogicGet for And, Or, Not
    void addInputPin(std::shared_ptr<LogicGate> pin);
    /// @brief for InputPin
    void addInputPin(int8_t pin);

protected:
    std::vector<std::shared_ptr<LogicGate>> ipin_vector_;
    int8_t output_; 

    virtual void compute() = 0; 
};

class AndGate : public LogicGate {
public:
    AndGate(std::vector<std::shared_ptr<LogicGate>> inputVector);

protected:
    void compute() override;
};

class OrGate : public LogicGate {
public:
    OrGate(std::vector<std::shared_ptr<LogicGate>> inputVector);

protected:
    void compute() override;
};

class NotGate : public LogicGate {
public:
    NotGate(std::vector<std::shared_ptr<LogicGate>> inputVector);

protected:
    void compute() override;
};

class InputPin : public LogicGate {
public:
    InputPin(std::vector<std::shared_ptr<LogicGate>> inputVector);
};

class OutputPin : public LogicGate {
public:
    OutputPin(std::vector<std::shared_ptr<LogicGate>> inputVector);
};

#endif // LOGICGATE_H
