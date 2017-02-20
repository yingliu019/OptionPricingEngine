//
//  BinaryCallPayoff.hpp
//  OptionPricer
//
//  Created by YingLiu on 1/24/17.
//  Copyright © 2017 YingLiu. All rights reserved.
//

#ifndef BinaryCallPayoff_hpp
#define BinaryCallPayoff_hpp

#include <stdio.h>
#include "Payoff.hpp"

class BinaryCallPayoff : public Payoff {

public:
    BinaryCallPayoff(double k);

    bool knockCondition() const;
    double getBarrier() const;
    int getPayoffType() const;
    
    double expirationPayoff(double ST) const;
    double intermediatePayoff(double St, double discountedExpectation) const;
};

#endif /* BinaryCallPayoff_hpp */
