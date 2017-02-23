//
//  Option.hpp
//  OptionPricer
//
//  Created by YingLiu on 1/24/17.
//  Copyright © 2017 YingLiu. All rights reserved.
//

#ifndef Option_hpp
#define Option_hpp

#include <stdio.h>
#include "Payoff.hpp"
#include "PricingEngine.hpp"
#include <memory>

using namespace std;

class Option {

public:
    // once the payoff is set, it shouldn't change
    Option(const shared_ptr<Payoff>& payoff);
    
    void SetpricingEngine(shared_ptr<PricingEngine> engine);
    virtual double Price() = 0;
    
protected:
    shared_ptr<Payoff> payoff_;
    shared_ptr<PricingEngine> engine_;

};

#endif /* Option_hpp */




