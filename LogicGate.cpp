#include "LogicGate.h"

// LogicGate
LogicGate::LogicGate() : output_(UNINITIALIZED) {}

bool LogicGate::isHaveAlliPinValue() const {
    for (const auto& pin : ipin_vector_) {
        if (pin == nullptr || pin->getOutput() == UNINITIALIZED) {
            return false;
        }
    }
    return true;
}

int8_t LogicGate::getOutput() {
    // if (!isHaveAlliPinValue()) {
    //     throw std::runtime_error("Not all input pins have values.");
    // }
    // compute();
    return output_;
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
// AndGate::AndGate(std::vector<std::shared_ptr<LogicGate>> inputVector) {
//     ipin_vector_ = inputVector;
// }

void AndGate::compute() {
    std::cout<<"And comput: "<<std::endl;
    output_ = 1;
    for (const auto& pin : ipin_vector_) {
        std::cout<<pin<<", ";
        int8_t pinOutput = pin->getOutput();
        if (pinOutput == UNINITIALIZED) {
            output_ = UNINITIALIZED;
            return;
        }
        output_ &= pinOutput;
    }
}

// OrGate
// OrGate::OrGate(std::vector<std::shared_ptr<LogicGate>> inputVector) {
//     ipin_vector_ = inputVector;
// }

void OrGate::compute() {
    std::cout<<"Or comput: "<<std::endl;
    output_ = 0;
    for (const auto& pin : ipin_vector_) {
        std::cout<<pin<<", ";
        int8_t pinOutput = pin->getOutput();
        if (pinOutput == UNINITIALIZED) {
            output_ = UNINITIALIZED;
            return;
        }
        output_ |= pinOutput;
    }
}

// NotGate
// NotGate::NotGate(std::vector<std::shared_ptr<LogicGate>> inputVector) {
//     if (inputVector.size() != 1) {
//         throw std::invalid_argument("NotGate requires exactly one input.");
//     }
//     ipin_vector_ = inputVector;
// }

void NotGate::compute() {
    std::cout<<"Not comput: "<<std::endl;
    if (ipin_vector_.size() != 1) {
        throw std::logic_error("NotGate requires exactly one input.");
    }
    std::cout<<ipin_vector_[0]<<", ";
    int8_t pinOutput = ipin_vector_[0]->getOutput();
    if (pinOutput == UNINITIALIZED) {
        output_ = UNINITIALIZED;
    } else {
        output_ = !pinOutput;
    }
    
}

// InputPin
// InputPin::InputPin(std::vector<std::shared_ptr<LogicGate>> inputVector) {
//     if(inputVector.size() > 0){
//         throw std::invalid_argument("Insert InputPin value must throught by addInput function");
//     }
//     output_ = UNINITIALIZED;
// }
// InputPin::InputPin(int8_t input) {
//     output_ = input;
// }
void InputPin::compute() {
    // InputPin does not need to compute, output is already set.
    std::cout << "InputPin does not need to compute, output is already set." << std::endl;
}

