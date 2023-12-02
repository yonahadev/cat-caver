//
//  main.cpp
//  cat-caver
//
//  Created by tom on 2023/12/02.
//
#include "application.hpp"
#include <iostream>

int main() {
    
    try {
        runApplication();
    } catch (const char *errorMessage) {
        std::cout << "Caught error: " << errorMessage << "\n";
    }
    std::cout << "Terminating Cat Caver" << "\n";
    return 0;
}
