#include <iostream>
#include <time.h>

int main()
{
    int x;
    std::cout << "Specify a positive number" << std::endl;
    std::cin >> x;
    unsigned int x_size = 8;
    unsigned int y_size = 9;
    unsigned int z_size = 11;
    unsigned int array[x_size][y_size][z_size];
    // random seed
    srand (time(NULL));
    for(int i = 0; i < x_size; i++) {
        std::cout << "{ ";
        for(int j = 0; j < y_size; j++) {
            std::cout << "{ ";
            for(int k = 0; k < z_size; k++) {
                int random_number = rand() % x;
                array[i][j][k] = random_number;
                std::cout << random_number;
                if(k < z_size-1) {
                    std::cout << ", ";
                }
            }
            std::cout << " }";
            if(j < y_size-1) {
                std::cout << "\t";
            }
        }
        std::cout << " }" << std::endl;
    }
}