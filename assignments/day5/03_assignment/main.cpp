#include <iostream>
#include <time.h>
#include <set>

int main(){
    srand (time(NULL));
    std::set<int> a;
    for(int i=0; i < 1024; i++) {
        int random_number = rand() % 1000;
        a.insert(random_number);
    }
/*
    for(auto elem : a) {
        std::cout << elem << std::endl;
    }
*/
    //new random number
    int r = rand() % 1000;
    std::cout << "Random number: " << r << std::endl << "Boundries: Lower - " << *(--a.lower_bound(r)) << ", Upper - " << *(a.upper_bound(r)) << std::endl;
}