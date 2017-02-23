//
//  MCForEuropean.hpp
//  OptionPricer
//
//  Created by YingLiu on 1/25/17.
//  Copyright © 2017 YingLiu. All rights reserved.
//

#ifndef MCForEuropean_hpp
#define MCForEuropean_hpp

#include <stdio.h>
#include <cassert>
#include <iostream>
#include <string>
#include "PricingEngine.hpp"

class MCForEuropean : public PricingEngine {

public:
    MCForEuropean(const shared_ptr<StochasticProcess>& stochasticProcess, double paths)
    : stochasticProcess_(stochasticProcess), paths_(paths)
    {}
    
    double PriceForAmerican(const shared_ptr<Payoff>& payoff) {
        return 0.0;
    }
    virtual double PriceForEuropean(const shared_ptr<Payoff>& payoff) = 0;
    //double Delta(double K);
    
protected:
    unsigned int paths_;
    shared_ptr<StochasticProcess> stochasticProcess_;
};

#endif /* MCForEuropean_hpp */








