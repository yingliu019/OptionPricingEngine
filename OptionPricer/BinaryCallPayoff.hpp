//
//  BinaryCallPayoff.hpp
//  OptionPricer
//
//  Created by 刘颖 on 1/24/17.
//  Copyright © 2017 刘颖. All rights reserved.
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
