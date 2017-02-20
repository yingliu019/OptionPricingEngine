//
//  UpAndOutPut.cpp
//  OptionPricer
//
//  Created by 刘颖 on 1/24/17.
//  Copyright © 2017 刘颖. All rights reserved.
//

#include "UpAndOutPutPayoff.hpp"

// also there is down and out call
// discrete monitering time and continuous monitering time
// numerical HW 1
// addition variable: H and observation interval
// implied volatility calculation, hw 2 t1


UpAndOutPutPayoff::UpAndOutPutPayoff(double k, double H)
: Payoff(k), H_(H)
{}

bool UpAndOutPutPayoff::knockCondition() const {
    return true;
}

double UpAndOutPutPayoff::getBarrier() const {
    return H_;
}

//Checking to see if the option is out of money or in the money to determine payoff
double UpAndOutPutPayoff::expirationPayoff(double ST) const {
    // H must be larger than strike
    if (strike_ < ST) {
        return 0;
    } else {
        return strike_ - ST;
    }
}

double UpAndOutPutPayoff::intermediatePayoff(double St, double discountedExpectation) const {
    double earlyExercise = expirationPayoff(St);
    return earlyExercise > discountedExpectation ? earlyExercise : discountedExpectation;
}

/*
 string PutPayoff::getPayoffType() const {
 return "put";
 }
 */

int UpAndOutPutPayoff::getPayoffType() const {
    return 5;
}
