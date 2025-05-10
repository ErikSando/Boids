#include <iostream>

#include "Program.h"

int main() {
    Program program("2D Boid Simulation", 960, 540);
    program.frame_rate = 0;
    //program.frame_rate = 0;
    program.Run();

    std::cout << "Program finished" << std::endl;

    return 0;
}