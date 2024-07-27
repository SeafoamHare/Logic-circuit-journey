
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>


class LogicGate {
public:
    LogicGate() : output_(-1) {}

    // 檢查所有輸入引腳是否都有數值
    bool isHaveAlliPinValue() const {
        for (const auto& pin : ipin_) {
            if (pin == nullptr) {
                return false;
            }
        }
        return true;
    }

    // 獲取輸出
    int getOutput() const {
        if (!isHaveAlliPinValue()) {
            throw std::runtime_error("Not all input pins have values.");
        }
        return output_;
    }

protected:
    std::vector<std::shared_ptr<LogicGate>> ipin_;  //  iPin for this gate
    int output_;  // 輸出

    virtual void compute() = 0;  // gate apply logic
};
