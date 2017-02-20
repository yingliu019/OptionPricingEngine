//
//  Payoff.cpp
//  OptionPricer
//
//  Created by 刘颖 on 1/24/17.
//  Copyright © 2017 刘颖. All rights reserved.
//

#include "Payoff.hpp"

//Constructor and destructor
Payoff::Payoff(double k) : strike_(k)
{}


//Strike Setters and Getters
double Payoff::GetK() {
    return strike_;
}

void Payoff::SetK(double k) {
    strike_ = k;
}

