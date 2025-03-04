#include "../inc/LogicGate.h"

// LogicGate
LogicGate::LogicGate() : output_(UNINITIALIZED) {}

int8_t LogicGate::getOutput() {
    return output_;
}

void LogicGate::reset() {
    output_ = UNINITIALIZED;
}
void LogicGate::addInputPin(std::shared_ptr<LogicGate> pin) {
    ipin_vector_.push_back(pin);
}

void LogicGate::addInputPin(int8_t input) {
    if (input == 0 || input == 1) {
        output_ = input;
    } else {
        throw std::invalid_argument("Input value must be 0 or 1");
    }
}

// AndGate
void AndGate::compute() {
    output_ = 1;
    for (const auto& pin : ipin_vector_) {
        int8_t pinOutput = pin->getOutput();
        if (pinOutput == UNINITIALIZED) {
            output_ = UNINITIALIZED;
            return;
        }
        output_ &= pinOutput;
    }
}

// OrGate
void OrGate::compute() {
    output_ = 0;
    for (const auto& pin : ipin_vector_) {
        int8_t pinOutput = pin->getOutput();
        if (pinOutput == UNINITIALIZED) {
            output_ = UNINITIALIZED;
            return;
        }
        output_ |= pinOutput;
    }
}

// NotGate
void NotGate::compute() {
    if (ipin_vector_.size() != 1) {
        throw std::logic_error("NotGate requires exactly one input.");
    }
    int8_t pinOutput = ipin_vector_[0]->getOutput();
    if (pinOutput == UNINITIALIZED) {
        output_ = UNINITIALIZED;
    } else {
        output_ = !pinOutput;
    }
    
}

// InputPin
void InputPin::compute() {
    throw std::logic_error("InputPin does not need to compute, output is already set.");
}

