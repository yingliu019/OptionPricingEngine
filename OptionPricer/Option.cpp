//
//  Option.cpp
//  OptionPricer
//
//  Created by 刘颖 on 1/24/17.
//  Copyright © 2017 刘颖. All rights reserved.
//

#include "Option.hpp"

Option::Option(const shared_ptr<Payoff>& payoff)
: payoff_(payoff)
{}

void Option::SetpricingEngine(shared_ptr<PricingEngine> engine) {
    engine_ = engine;
}
