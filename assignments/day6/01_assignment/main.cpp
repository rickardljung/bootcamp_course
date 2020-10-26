#include <bitset>
#include <iostream>

typedef struct struct_vehicle_info_field {
    unsigned  lights_rear:1;
    unsigned  lights_pass:1;
    unsigned  lights_driver:1;
    unsigned  door_rear_pass:1;
    unsigned  door_rear_driver:1;
    unsigned  door_pass:1;
    unsigned  door_driver:1;
    unsigned  window_rear_pass:1;
    unsigned  window_rear_driver:1;
    unsigned  window_pass:1;
    unsigned  window_driver:1;
    unsigned  belt_rear_middle:1;
    unsigned  belt_rear_pass:1;
    unsigned  belt_rear_driver:1;
    unsigned  belt_pass:1;
    unsigned  belt_driver:1;
} vehicle_info_field;

void printVehicleInfoField(const vehicle_info_field &_f) {
    std::cout << "----------------" << std::endl;
    std::cout << "belt_driver: " << static_cast<int>(_f.belt_driver) << std::endl;
    std::cout << "belt_pass " << static_cast<int>(_f.belt_pass) << std::endl;
    std::cout << "belt_rear_driver " << static_cast<int>(_f.belt_rear_driver) << std::endl;
    std::cout << "belt_rear_pass " << static_cast<int>(_f.belt_rear_pass) << std::endl;
    std::cout << "belt_rear_middle " << static_cast<int>(_f.belt_rear_middle) << std::endl;
    std::cout << "window_driver " << static_cast<int>(_f.window_driver) << std::endl;
    std::cout << "window_pass " << static_cast<int>(_f.window_pass) << std::endl;
    std::cout << "window_rear_driver " << static_cast<int>(_f.window_rear_driver) << std::endl;
    std::cout << "window_rear_pass " << static_cast<int>(_f.window_rear_pass) << std::endl;
    std::cout << "door_driver " << static_cast<int>(_f.door_driver) << std::endl;
    std::cout << "door_pass " << static_cast<int>(_f.door_pass) << std::endl;
    std::cout << "door_rear_driver " << static_cast<int>(_f.door_rear_driver) << std::endl;
    std::cout << "door_rear_pass " << static_cast<int>(_f.door_rear_pass) << std::endl;
    std::cout << "lights_driver " << static_cast<int>(_f.lights_driver) << std::endl;
    std::cout << "lights_pass " << static_cast<int>(_f.lights_pass) << std::endl;
    std::cout << "lights_rear " << static_cast<int>(_f.lights_rear) << std::endl;
    std::cout << "----------------" << std::endl;
}

int main() {
    uint16_t vehicle_info_bits = 0b1011101001011011;
    vehicle_info_field *info = reinterpret_cast<vehicle_info_field*>(&vehicle_info_bits);
    printVehicleInfoField(*info);
    return 0;
}