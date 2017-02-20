//
//  AmericanOption.cpp
//  OptionPricer
//
//  Created by 刘颖 on 1/24/17.
//  Copyright © 2017 刘颖. All rights reserved.
//

#include "AmericanOption.hpp"

AmericanOption::AmericanOption(const shared_ptr<Payoff>& payoff)
: Option(payoff)
{}

double Price();

double AmericanOption::Price() {
    return engine_->PriceForAmerican(payoff_);
}
