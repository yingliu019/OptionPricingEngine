//
//  PutPayoff.hpp
//  OptionPricer
//
//  Created by 刘颖 on 1/24/17.
//  Copyright © 2017 刘颖. All rights reserved.
//

#ifndef PutPayoff_hpp
#define PutPayoff_hpp

#include <stdio.h>

#include"Payoff.hpp"


class PutPayoff : public Payoff {

public:
    PutPayoff(double k);
    
    bool knockCondition() const;
    double getBarrier() const;
    
    int getPayoffType() const;
    double expirationPayoff(double ST) const;
    double intermediatePayoff(double St, double discountedExpectation) const;

//private:
    //const int payoffType_;
    //PayoffType payoffType_;
};

#endif /* PutPayoff_hpp */
