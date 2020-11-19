#include "engine_simulator.h"
#include "user_input.h"
#include <iostream>

int hp = 1000;
int max_rpm = 9000;

int main(){
    Engine engine(hp, max_rpm);

    engine.Ignition(1, 0, 20, 0);
    if(engine.get_eng_sts()) std::cout << "Ignition is on!" << std::endl;
    for(int i=0;i<100000;i++){
        engine.RPM(100,0,1);
    }
    std::cout << "RPM based on acc: " << (int)engine.get_eng_rpm() << std::endl;

    engine.ActualRPM(20, 100);
    std::cout << "RPM based on speed 20: " << (int)engine.get_eng_rpm() << std::endl;

    engine.ActualRPM(40, 100);
    std::cout << "RPM based on speed 40: "<< (int)engine.get_eng_rpm() << std::endl;

    engine.Ignition(0, 0, 0, 0);
    if(!engine.get_eng_sts()) std::cout << "Ignition is off!" << std::endl;
}