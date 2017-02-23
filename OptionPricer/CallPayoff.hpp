//
//  CallPayoff.hpp
//  OptionPricer
//
//  Created by YingLiu on 1/24/17.
//  Copyright © 2017 YingLiu. All rights reserved.
//

#ifndef CallPayoff_hpp
#define CallPayoff_hpp

#include <stdio.h>

#include"Payoff.hpp"

class CallPayoff : public Payoff {

public:
    CallPayoff(double k);
    
    bool knockCondition() const;
    double getBarrier() const;
    
    int getPayoffType() const;
    double expirationPayoff(double ST) const;
    double intermediatePayoff(double St, double discountedExpectation) const;

};

#endif /* CallPayoff_hpp */
