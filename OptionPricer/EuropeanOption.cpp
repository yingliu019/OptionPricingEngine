//
//  EuropeanOption.cpp
//  OptionPricer
//
//  Created by 刘颖 on 1/24/17.
//  Copyright © 2017 刘颖. All rights reserved.
//

#include "EuropeanOption.hpp"

EuropeanOption::EuropeanOption(const shared_ptr<Payoff>& payoff)
: Option(payoff)
{}

double EuropeanOption::Price() {
    return engine_->PriceForEuropean(payoff_);
}
