//
//  BinaryPutPayoff.hpp
//  OptionPricer
//
//  Created by 刘颖 on 1/24/17.
//  Copyright © 2017 刘颖. All rights reserved.
//

#ifndef BinaryPutPayoff_hpp
#define BinaryPutPayoff_hpp

#include <stdio.h>

#include "Payoff.hpp"

class BinaryPutPayoff : public Payoff {

public:
    BinaryPutPayoff(double k);
    
    bool knockCondition() const;
    double getBarrier() const;
    int getPayoffType() const;
    
    double expirationPayoff(double ST) const;
    double intermediatePayoff(double St, double discountedExpectation) const;
};

#endif /* BinaryPutPayoff_hpp */
