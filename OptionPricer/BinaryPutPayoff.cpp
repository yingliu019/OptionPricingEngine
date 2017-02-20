//
//  BinaryPutPayoff.cpp
//  OptionPricer
//
//  Created by YingLiu on 1/24/17.
//  Copyright © 2017 YingLiu. All rights reserved.
//

#include "BinaryPutPayoff.hpp"

BinaryPutPayoff::BinaryPutPayoff(double k) : Payoff(k)
{}


//Checking to see if the option is out of money or in the money to determine payoff
double BinaryPutPayoff::expirationPayoff(double ST) const {
    if (strike_<ST) {
        return 0;
    } else {
        return 1.0;
    }
}

bool BinaryPutPayoff::knockCondition() const {
    return false;
}

double BinaryPutPayoff::getBarrier() const {
    return 0;
}


double BinaryPutPayoff::intermediatePayoff(double St, double discountedExpectation) const {
    double earlyExercise = expirationPayoff(St);
    return earlyExercise>discountedExpectation ? earlyExercise : discountedExpectation;
}


int BinaryPutPayoff::getPayoffType() const {
    return 4;
}


