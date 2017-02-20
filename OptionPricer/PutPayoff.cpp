//
//  PutPayoff.cpp
//  OptionPricer
//
//  Created by 刘颖 on 1/24/17.
//  Copyright © 2017 刘颖. All rights reserved.
//

#include "PutPayoff.hpp"

PutPayoff::PutPayoff(double k)
    : Payoff(k)
{}

bool PutPayoff::knockCondition() const {
    return false;
}
double PutPayoff::getBarrier() const {
    return 0;
}

//Checking to see if the option is out of money or in the money to determine payoff
double PutPayoff::expirationPayoff(double ST) const {
    if (strike_ < ST) {
        return 0;
    } else {
        return strike_ - ST;
    }
}

double PutPayoff::intermediatePayoff(double St, double discountedExpectation) const {
    double earlyExercise = expirationPayoff(St);
    return earlyExercise > discountedExpectation ? earlyExercise : discountedExpectation;
}


int PutPayoff::getPayoffType() const {
    return 2;
}
