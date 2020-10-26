#include <bitset>
#include <iostream>

typedef struct struct_field {
    unsigned left:3;
    unsigned right:3;
    unsigned rear:3;
    unsigned front:3;
    unsigned speed:4;
} field;

uint16_t encode(int speed, int front, int rear, int right, int left) {
    uint16_t output = 0;
    output |= std::min(speed/20, 0b1111) << 12;
    output |= std::min(front/150, 0b111) << 9;
    output |= std::min(rear/150, 0b111) << 6;
    output |= std::min(right/150, 0b111) << 3;
    output |= std::min(left/150, 0b111);
    //std::cout << "output: " << std::bitset<16>(output) << std::endl;
    return output;
}

void detectCrash(uint16_t &info) {
    field *f = reinterpret_cast<field*>(&info);
    /*
    std::cout << "f->speed " << f->speed << std::endl;
    std::cout << "f->front " << f->front << std::endl;
    std::cout << "f->rear " << f->rear << std::endl;
    std::cout << "f->right " << f->right << std::endl;
    std::cout << "f->left " << f->left << std::endl;
    */
    if (f->front == 0) {
        std::cout << "Crash at front detected with speed " << f->speed*20 << std::endl;
    } else if(f->left == 0) {
        std::cout << "Crash at left detected with speed " << f->speed*20 << std::endl;
    } else if(f->right == 0) {
        std::cout << "Crash at right detected with speed " << f->speed*20 << std::endl;
    }else if(f->rear == 0) {
        std::cout << "Crash at rear detected with speed " << f->speed*20 << std::endl;
    }
}

int main() {
    uint16_t encoded = encode(199, 200, 999, 50, 350);
    detectCrash(encoded);
    return 0;
}