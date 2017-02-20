//
//  BinaryCallPayoff.cpp
//  OptionPricer
//
//  Created by YingLiu on 1/24/17.
//  Copyright © 2017 YingLiu. All rights reserved.
//

#include "BinaryCallPayoff.hpp"

BinaryCallPayoff::BinaryCallPayoff(double k) : Payoff(k)
{}

//Checking to see if the option is out of money or in the money to determine payoff
double BinaryCallPayoff::expirationPayoff(double ST) const {
    if (strike_<ST) {
        return 1.0;
    } else {
        return 0.0;
    }
}

bool BinaryCallPayoff::knockCondition() const {
    return false;
}
double BinaryCallPayoff::getBarrier() const {
    return 0;
}


double BinaryCallPayoff::intermediatePayoff(double St, double discountedExpectation) const {
    double earlyExercise = expirationPayoff(St);
    return earlyExercise>discountedExpectation ? earlyExercise : discountedExpectation;
}

int BinaryCallPayoff::getPayoffType() const {
    return 3;
}
