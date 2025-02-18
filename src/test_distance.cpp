#include "distanceManager.hpp"
#include <iostream>

int main () {
    CDistanceManager dm;
    printf("CDistanceManager was constructed\n");
    // std::cout << dm(0,0) << std::endl;
    // std::cout << dm(0,4) << std::endl;
    // std::cout << dm(0,6) << std::endl;
    // std::cout << dm(0,7) << std::endl;
    // std::cout << dm(0,8) << std::endl;

    // std::cout << dm(1,0) << std::endl;
    printf("dm(0,i)\n");
    for (int i = 0; i < 48; i ++) {
        std::cout << i << ": " << dm(0,i) << " ";
        std::cout << std::endl;
    }
    printf("dm(1,i)\n");
    for (int i = 0; i < 48; i ++) {
        std::cout << i << ": " << dm(1,i) << " ";
        std::cout << std::endl;
    }
}