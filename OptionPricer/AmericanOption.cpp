//
//  AmericanOption.cpp
//  OptionPricer
//
//  Created by YingLiu on 1/24/17.
//  Copyright © 2017 YingLiu. All rights reserved.
//

#include "AmericanOption.hpp"

AmericanOption::AmericanOption(const shared_ptr<Payoff>& payoff)
: Option(payoff)
{}

double Price();

double AmericanOption::Price() {
    return engine_->PriceForAmerican(payoff_);
}
