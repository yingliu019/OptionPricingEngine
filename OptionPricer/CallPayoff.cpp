//
//  CallPayoff.cpp
//  OptionPricer
//
//  Created by 刘颖 on 1/24/17.
//  Copyright © 2017 刘颖. All rights reserved.
//

#include "CallPayoff.hpp"

CallPayoff::CallPayoff(double k) : Payoff(k)
{}

double CallPayoff::expirationPayoff(double ST) const {
    if (strike_<ST) {
        return ST-strike_;
    } else {
        return 0.0;
    }
}

bool CallPayoff::knockCondition() const {
    return false;
}
double CallPayoff::getBarrier() const {
    return 0;
}


double CallPayoff::intermediatePayoff(double St, double discountedExpectation) const {
    double earlyExercise = expirationPayoff(St);
    return earlyExercise>discountedExpectation ? earlyExercise : discountedExpectation;
}

int CallPayoff::getPayoffType() const {
    return 1;
}
