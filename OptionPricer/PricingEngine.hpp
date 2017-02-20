//
//  PricingEngine.hpp
//  OptionPricer
//
//  Created by 刘颖 on 1/24/17.
//  Copyright © 2017 刘颖. All rights reserved.
//

#ifndef PricingEngine_hpp
#define PricingEngine_hpp

#include <stdio.h>

#include "Payoff.hpp"
#include "StochasticProcess.hpp"

#include <memory>

using std::shared_ptr;

class PricingEngine {

public:

    PricingEngine()
    {}
    
    virtual double PriceForAmerican(const shared_ptr<Payoff>& payoff) = 0;
    virtual double PriceForEuropean(const shared_ptr<Payoff>& payoff) = 0;
    //virtual double Delta(const shared_ptr<Payoff>& payoff) = 0;
    
    
};

#endif /* PricingEngine_hpp */
