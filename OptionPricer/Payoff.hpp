//
//  Payoff.hpp
//  OptionPricer
//
//  Created by 刘颖 on 1/24/17.
//  Copyright © 2017 刘颖. All rights reserved.
//

#ifndef Payoff_hpp
#define Payoff_hpp

#include <stdio.h>

#include <String>

using namespace std;

enum PayoffType {call = 1, put = 2, binaryCall = 3, binaryPut = 4, upAndOutPut = 5};

class Payoff {

public:
    
    Payoff(double strike);

    double GetK();
    void SetK(double k);
    
    virtual int getPayoffType() const = 0;
    virtual bool knockCondition() const = 0;
    virtual double getBarrier() const = 0;
    
    virtual double expirationPayoff(double ST) const = 0;
    virtual double intermediatePayoff(double St, double discountedExpectation) const = 0;
    
protected:
    double strike_;

};

#endif /* Payoff_hpp */
