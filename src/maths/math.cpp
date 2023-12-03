//
//  math.cpp
//  Executable
//
//  Created by tom on 2023/10/10.
//

#include "math.hpp"
#include <iostream>
#include <random>

float radians(float degrees) {
    return (degrees * M_PI) / 180;
}

int getRandomInt(const int lower, const int upper) {
    std::random_device randomDevice;
    std::default_random_engine engine(randomDevice());
    std::uniform_int_distribution<int> integerGenerator(lower,upper);
    int randomInt = integerGenerator(engine);
    return randomInt;
}

int min(int number1,int number2) {
    if (number1 <= number2) {
        return number1;
    } else {
        return number2;
    }
}
 
int getHCF(int number1, int number2) {
    int HCF = 1;
    int currentNumber = 1;
    
    while (currentNumber < min(number1,number2)/2) {
        if (number1 % currentNumber == 0 && number2 % currentNumber == 0 ) {
            HCF = currentNumber;
        }
        currentNumber += 1;
    }
    
    return HCF;
}
