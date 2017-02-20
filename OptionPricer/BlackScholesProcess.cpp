//
//  BlackScholesProcess.cpp
//  OptionPricer
//
//  Created by 刘颖 on 2/11/17.
//  Copyright © 2017 刘颖. All rights reserved.
//

#include "BlackScholesProcess.hpp"

BlackScholesProcess::BlackScholesProcess(double S, double rate, double div, double vol, double expiry)
: S0_(S), r_(rate), q_(div), sigma_(vol), T_(expiry)
{}

double BlackScholesProcess::GetInitialStock() const {
    return S0_;
}

double BlackScholesProcess::GetInterestRate() const {
    return r_;
}

double BlackScholesProcess::GetDividend() const {
    return q_;
}

double BlackScholesProcess::GetVolatility() const {
    return sigma_;
}

double BlackScholesProcess::GetMaturity() const {
    return T_;
}
