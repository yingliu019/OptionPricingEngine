//
//  Option.cpp
//  OptionPricer
//
//  Created by YingLiu on 1/24/17.
//  Copyright © 2017 YingLiu. All rights reserved.
//

#include "Option.hpp"

Option::Option(const shared_ptr<Payoff>& payoff)
: payoff_(payoff)
{}

void Option::SetpricingEngine(shared_ptr<PricingEngine> engine) {
    engine_ = engine;
}
