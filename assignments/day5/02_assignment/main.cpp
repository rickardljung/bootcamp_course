#include <iostream>
#include <time.h>
#include<bits/stdc++.h>

int main(){

    // random seed
    srand (time(NULL));
    int upper_limit = 33;
    std::pair <int, int> a[upper_limit+1];
    for(int i=0; i< 10000; i++) {
        if (i < upper_limit+1) {
            a[i].second = i;
        }
        int random_number = rand() % (upper_limit+1);
        a[random_number].first = a[random_number].first + 1;
    }

    sort(a, a+upper_limit+1);

    for(auto elem : a) {
        std::cout << elem.first << " " << elem.second << std::endl;
    }

    /*
    auto comp = [&](auto a, auto b) {
        return a > b;
    };
    srand (time(NULL));
    int upper_limit = 33;
    //std::map<int, int> m;
    std::map<int, int, decltype(comp)> m(comp);
    for(int i=0; i< 10000; i++) {
        int random_number = rand() % (upper_limit+1);
        m[random_number] = m[random_number] + 1;
    }

    for(auto elem : m) {
        std::cout << elem.first << " " << elem.second << "\n";
    }

    */
}