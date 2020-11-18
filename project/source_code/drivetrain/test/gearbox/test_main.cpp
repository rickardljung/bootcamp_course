
#include <iostream>
#include "gearbox_simulator.h"

//g++ test_main.cpp ../../src/gearbox_simulator.cpp -I ../../../utils/include/ -I ../../include/

int main()
{
    double gear_ratios[] = {3.00, 3.18, 2.26, 1.68, 1.29, 1.06, 0.88};
    Gearbox g(gear_ratios, 7);

    std::cout << "gear_lever: " << static_cast<int>(g.get_gear_lever_position()) << std::endl;
    std::cout << "gear_ratio: " << (g.get_gear_ratio()) << std::endl;
    std::cout << std::endl;

    g.GearLeverPosition(D, 0, 0);
    std::cout << "gear_lever: " << static_cast<int>(g.get_gear_lever_position()) << std::endl;
    std::cout << "gear_ratio: " << (g.get_gear_ratio()) << std::endl;
    std::cout << std::endl;

    g.GearLeverPosition(R, 0, 100);
    std::cout << "gear_lever: " << static_cast<int>(g.get_gear_lever_position()) << std::endl;
    std::cout << "gear_ratio: " << (g.get_gear_ratio()) << std::endl;
    std::cout << std::endl;

    g.GearLeverPosition(D, 0, 100);
    std::cout << "gear_lever: " << static_cast<int>(g.get_gear_lever_position()) << std::endl;
    std::cout << "gear_ratio: " << (g.get_gear_ratio()) << std::endl;
    std::cout << std::endl;

    g.GearNumber(900);
    std::cout << "RPM 900 " << std::endl;
    std::cout << "gear_number: " << static_cast<int>(g.get_gear_number()) << std::endl;
    std::cout << "gear_ratio: " << (g.get_gear_ratio()) << std::endl;
    std::cout << std::endl;

    g.GearNumber(2000);
    std::cout << "RPM 2000" << std::endl;
    std::cout << "gear_number: " << static_cast<int>(g.get_gear_number()) << std::endl;
    std::cout << "gear_ratio: " << (g.get_gear_ratio()) << std::endl;
    std::cout << std::endl;

    g.GearNumber(6000);
    std::cout << "RPM 6000" << std::endl;
    std::cout << "gear_number: " << static_cast<int>(g.get_gear_number()) << std::endl;
    std::cout << "gear_ratio: " << (g.get_gear_ratio()) << std::endl;
    std::cout << std::endl;

    g.GearNumber(3000);
    std::cout << "RPM 3000" << std::endl;
    std::cout << "gear_number: " << static_cast<int>(g.get_gear_number()) << std::endl;
    std::cout << "gear_ratio: " << (g.get_gear_ratio()) << std::endl;
    std::cout << std::endl;

    g.GearNumber(7000);
    std::cout << "RPM 7000" << std::endl;
    std::cout << "gear_number: " << static_cast<int>(g.get_gear_number()) << std::endl;
    std::cout << "gear_ratio: " << (g.get_gear_ratio()) << std::endl;
    std::cout << std::endl;

    g.GearNumber(1000);
    std::cout << "RPM 1000" << std::endl;
    std::cout << "gear_number: " << static_cast<int>(g.get_gear_number()) << std::endl;
    std::cout << "gear_ratio: " << (g.get_gear_ratio()) << std::endl;
    std::cout << std::endl;
}