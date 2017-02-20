//
//  UpAndOutPut.hpp
//  OptionPricer
//
//  Created by 刘颖 on 1/24/17.
//  Copyright © 2017 刘颖. All rights reserved.
//

#ifndef UpAndOutPut_hpp
#define UpAndOutPut_hpp

#include <stdio.h>
#include "Payoff.hpp"


class UpAndOutPutPayoff : public Payoff {
    
public:
    UpAndOutPutPayoff(double k, double H);
    
    
    int getPayoffType() const;
    bool knockCondition() const;
    double getBarrier() const;
    double expirationPayoff(double ST) const;
    double intermediatePayoff(double St, double discountedExpectation) const;
    
    //private:
    //const int payoffType_;
    //PayoffType payoffType_;
    
private:
    double H_;
};

#endif /* UpAndOutPut_hpp */
