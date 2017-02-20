//
//  NaiveMC.cpp
//  OptionPricer
//
//  Created by 刘颖 on 1/25/17.
//  Copyright © 2017 刘颖. All rights reserved.
//


#include "BlackScholesAnalytical.hpp"
#include <iostream>
#include <cmath>
#include <cassert>
#include <string>

using namespace std;


BlackScholesAnalytical::BlackScholesAnalytical(const shared_ptr<StochasticProcess>& stochasticProcess, double K)
    : stochasticProcess_(stochasticProcess), K_(K), NormalUtils_(0.0)
{}

void BlackScholesAnalytical::SetNormalUtils(double d)
{
    NormalUtils utils(d);
    NormalUtils_ = utils;  //now NormalUtils_ become an object in NormalUtilis class which equal to utils
}


double BlackScholesAnalytical::PriceForEuropean(const shared_ptr<Payoff>& payoff) {
    
    double S_0 = stochasticProcess_->GetInitialStock();
    double r = stochasticProcess_->GetInterestRate();
    double sigma = stochasticProcess_->GetVolatility();
    double T = stochasticProcess_->GetMaturity();
    double q =  stochasticProcess_->GetDividend();
    
    double F = S_0 * exp((r - q)* T);
    double d_1 = (log(F) - log(K_)) / (sigma * sqrt(T)) + sigma * sqrt(T) / 2;
    double d_2 = (log(F) - log(K_)) / (sigma * sqrt(T)) - sigma * sqrt(T) / 2;
    
    int payofftype = payoff->getPayoffType();

    double price = 0;
    
    switch (payofftype)
    {
        case call:
            price = (NormalUtils_.NormCdf(d_1) * F - NormalUtils_.NormCdf(d_2) * K_) * exp(-r * T);
        case put:
             price =  (NormalUtils_.NormCdf(-d_2) * K_ - NormalUtils_.NormCdf(-d_1) * F) * exp (-r * T) ;
        case binaryCall:
             price = 0;
        case binaryPut:
            price = 0;
        case upAndOutPut:
            price = -101;
        default:
            return 0;
    }
    assert(price != -101  && "analytical can't price barrier");
    assert(price != 0  && "unfinish this pricer");
    return price;
    
}

double BlackScholesAnalytical::PriceForAmerican(const shared_ptr<Payoff>& payoff) {
    double price = -101;
    assert(price != -101  && "Analytical Pricer is not for American Option");
    return -101;
}


/*
double BlackScholesAnalytical::Delta(const shared_ptr<Payoff>& payoff) {
    double S_0 = bsProcess_.S0_;
    double r = bsProcess_.r_;
    double sigma = bsProcess_.sigma_;
    double T = bsProcess_.T_;
    double q = bsProcess_.q_;
    
    double F = S_0 * exp((r - q)* T);
    double d_1 = (log(F) - log(K_)) / (sigma * sqrt(T)) + sigma * sqrt(T) / 2;
    
    int payoffType = payoff->getPayoffType();
    
    switch (payoffType)
    {
        case VanillaCall:
            return NormalUtils_.NormCdf(d_1);
        case VanillaPut:
            return NormalUtils_.NormCdf(d_1) - 1;
        default:
            return 0;
    }
}
 
double BlackScholesAnalytical::Gamma(const shared_ptr<Payoff>& payoff) {
    double S_0 = bsProcess_.S0_;
    double r = bsProcess_.r_;
    double sigma = bsProcess_.sigma_;
    double T = bsProcess_.T_;
    double q = bsProcess_.q_;
    
    double F = S_0 * exp((r - q)* T);
    double d_1 = (log(F) - log(K_)) / (sigma * sqrt(T)) + sigma * sqrt(T) / 2;
    
    int payoffType = payoff->getPayoffType();
    
    switch (payoffType)
    {
        case VanillaCall:
            return NormalUtils_.NormPdf(d_1) / (F * sigma * sqrt(T));
        case VanillaPut:
            return NormalUtils_.NormPdf(d_1) / (F * sigma * sqrt(T));
        default:
            return 0;
    }
}
*/

