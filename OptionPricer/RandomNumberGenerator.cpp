//
//  RandomNumberGenerator.cpp
//  OptionPricer
//
//  Created by YingLiu on 1/24/17.
//  Copyright © 2017 YingLiu. All rights reserved.
//


#define _USE_MATH_DEFINES
#include "RandomNumberGenerator.hpp"
#include <cmath>
//#include <time.h> for win
#include <ctime> //for mac
#include <cstdlib>

using namespace std;

void RandomNumberGenerator::SetSeed() {
    srand((unsigned int)time(nullptr));
}

double RandomNumberGenerator::RandomByBoxMuller() {
    double x, y = 0.0;
    do {
        x = rand();
    } while (x == 0);
    
    x /= (double)RAND_MAX;
    y = (double)rand() / RAND_MAX;
    return sqrt((-2.0) * log(x)) * cos(2 * M_PI * y);
}
