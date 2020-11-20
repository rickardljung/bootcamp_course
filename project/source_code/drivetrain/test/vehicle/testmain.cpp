#include "vehicle.h"
#include<bits/stdc++.h>

int main(){
    Engine engine(1000, 9000);
    double gear_ratios[] = {3.00, 3.50, 2.56, 1.88, 1.35, 1.00, 0.83};
    Gearbox gearbox(gear_ratios, 7);
    Vehicle vehicle(&gearbox, &engine, 3.42, 1000, 0.68);
    size_t i;
    auto start = std::clock();
    for (i = 0; i<1000000000; i++)
    {
        vehicle.VehicleSpeed(3,5);
    }
    auto finish = std::clock() - start;
    std::cout << "Execution time for " << i << " calls of VehicleSpeed(): "
                << (float)finish/CLOCKS_PER_SEC << std::endl;
    return 0;
}