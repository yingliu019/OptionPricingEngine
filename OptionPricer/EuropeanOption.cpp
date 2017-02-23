//
//  EuropeanOption.cpp
//  OptionPricer
//
//  Created by YingLiu on 1/24/17.
//  Copyright © 2017 YingLiu. All rights reserved.
//

#include "EuropeanOption.hpp"

EuropeanOption::EuropeanOption(const shared_ptr<Payoff>& payoff)
: Option(payoff)
{}

double EuropeanOption::Price() {
    return engine_->PriceForEuropean(payoff_);
}
