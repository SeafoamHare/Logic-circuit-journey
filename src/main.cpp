
#include "../inc/LogicCircuitController.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>

int main()
{
    LogicCircuitController textcontroller;
    try
    {
        textcontroller.run_Application();
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Exception in textcontroller.runApplication(): " << ex.what()
                  << std::endl;
    }

    return 0;
}