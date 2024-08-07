
#include "../inc/LogicCircuit.h"
#include "../inc/LogicGate.h"
#include "../inc/TextUI.h"
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>

/*-------------LogicGate---------------*/
// 僅用為測試 LogicGate 類
class TestLogicGate : public LogicGate
{
public:
    void compute() override
    {
        // 不需要具體實現，僅用於測試的功能
    }
};

// 測試 LogicGate 類
TEST(LogicGateTest, DefaultOutput)
{
    TestLogicGate gate;
    EXPECT_EQ(gate.getOutput(), UNINITIALIZED);
}

TEST(LogicGateTest, AddInputPin)
{
    TestLogicGate gate;
    gate.addInputPin(1);
    EXPECT_EQ(gate.getOutput(), 1);
}

TEST(LogicGateTest, AddInvalidInputPin)
{
    TestLogicGate gate;
    EXPECT_THROW(gate.addInputPin(2), std::invalid_argument);
}

TEST(LogicGateTest, Reset)
{
    TestLogicGate gate;
    gate.addInputPin(1);
    gate.reset();
    EXPECT_EQ(gate.getOutput(), UNINITIALIZED);
}

// 測試 AndGate 類
TEST(AndGateTest, ComputeAndGate)
{
    auto input1 = std::make_shared<InputPin>();
    auto input2 = std::make_shared<InputPin>();
    input1->addInputPin(1);
    input2->addInputPin(0);

    AndGate gate;
    gate.addInputPin(input1);
    gate.addInputPin(input2);
    gate.compute();
    EXPECT_EQ(gate.getOutput(), 0);

    input2->reset();
    input2->addInputPin(1);
    gate.compute();
    EXPECT_EQ(gate.getOutput(), 1);
}

// 測試 OrGate 類
TEST(OrGateTest, ComputeOrGate)
{
    auto input1 = std::make_shared<InputPin>();
    auto input2 = std::make_shared<InputPin>();
    input1->addInputPin(0);
    input2->addInputPin(0);

    OrGate gate;
    gate.addInputPin(input1);
    gate.addInputPin(input2);
    gate.compute();
    EXPECT_EQ(gate.getOutput(), 0);

    input2->reset();
    input2->addInputPin(1);
    gate.compute();
    EXPECT_EQ(gate.getOutput(), 1);
}

// 測試 NotGate 類
TEST(NotGateTest, ComputeNotGate)
{
    auto input = std::make_shared<InputPin>();
    input->addInputPin(1);

    NotGate gate;
    gate.addInputPin(input);
    gate.compute();
    EXPECT_EQ(gate.getOutput(), 0);

    input->reset();
    input->addInputPin(0);
    gate.compute();
    EXPECT_EQ(gate.getOutput(), 1);
}

TEST(NotGateTest, NotGateInvalidInput)
{
    NotGate gate;
    EXPECT_THROW(gate.compute(), std::logic_error);
}

// 測試 InputPin 類
TEST(InputPinTest, ComputeInputPin)
{
    InputPin pin;
    EXPECT_THROW(pin.compute(), std::logic_error);
}

/*-------------LogicCircuit---------------*/
TEST(LogicCircuitTest, OutputPinsCount)
{
    LogicCircuit circuit;

    // Test for File1.lcf
    ASSERT_TRUE(circuit.loadFromFile("File1.lcf"));
    EXPECT_EQ(circuit.getOutputPinsCount(), 1);

    // Test for File2.lcf
    ASSERT_TRUE(circuit.loadFromFile("File2.lcf"));
    EXPECT_EQ(circuit.getOutputPinsCount(), 3);
}

TEST(LogicCircuitTest, Simulation_File1)
{
    LogicCircuit circuit;
    ASSERT_TRUE(circuit.loadFromFile("File1.lcf"));

    // Test input {0, 1, 1} expecting output {0}
    std::vector<int8_t> inputs1 = {0, 1, 1};
    std::vector<int8_t> expected_outputs1 = {0};
    EXPECT_EQ(circuit.simuulate(inputs1), expected_outputs1);

    // Test input {1, 0, 1} expecting output {1}
    std::vector<int8_t> inputs2 = {1, 0, 1};
    std::vector<int8_t> expected_outputs2 = {1};
    EXPECT_EQ(circuit.simuulate(inputs2), expected_outputs2);
}

TEST(LogicCircuitTest, Simulation_File2)
{
    LogicCircuit circuit;
    ASSERT_TRUE(circuit.loadFromFile("File2.lcf"));

    // Test input {1, 0, 0, 1} expecting output {1, 0, 0}
    std::vector<int8_t> inputs1 = {1, 0, 0, 1};
    std::vector<int8_t> expected_outputs1 = {1, 0, 0};
    EXPECT_EQ(circuit.simuulate(inputs1), expected_outputs1);

    // Test input {1, 0, 1, 0} expecting output {1, 0, 1}
    std::vector<int8_t> inputs2 = {1, 0, 1, 0};
    std::vector<int8_t> expected_outputs2 = {1, 0, 1};
    EXPECT_EQ(circuit.simuulate(inputs2), expected_outputs2);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
