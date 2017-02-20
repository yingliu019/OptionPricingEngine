//
//  NaiveMC.cpp
//  OptionPricer
//
//  Created by 刘颖 on 1/25/17.
//  Copyright © 2017 刘颖. All rights reserved.
//


#include "OrdinaryMC.hpp"
#include "RandomNumberGenerator.hpp"
#include <cmath>

using namespace std;

OrdinaryMC::OrdinaryMC(const shared_ptr<StochasticProcess>& stochasticProcess, double paths)
: MCForEuropean(stochasticProcess, paths)
{}


double OrdinaryMC::PriceForEuropean(const shared_ptr<Payoff>& payoff) {
    double S_0 = stochasticProcess_->GetInitialStock();
    double r = stochasticProcess_->GetInterestRate();
    double sigma = stochasticProcess_->GetVolatility();
    double T = stochasticProcess_->GetMaturity();
    //double q =  stochasticProcess_->GetDividend();
    
    bool flag = payoff->knockCondition();
    assert(flag != true && "not recommend use MC for barrier");
    
    RandomNumberGenerator gen;
    gen.SetSeed();
    
    double runningSum = 0.0;
    
    for (unsigned int i = 0; i < paths_; i++) {
        double z = gen.RandomByBoxMuller();
        double S_T = S_0 * exp((r - sigma * sigma / 2.0) * T + sigma * z * sqrt(T));
        double P = payoff->expirationPayoff(S_T);
        runningSum += P;
    }
    return exp(-r*T) * (runningSum / paths_);
}

double OrdinaryMC::PriceForAmerican(const shared_ptr<Payoff>& payoff) {
    double price = -101;
    assert(price != -101  && "Ordinary MC Pricer is not for American Option");
    return -101;
}



// 怎么加，在哪里加
// double OrdinaryMC::Delta(double K) {
//     double epsilon = 0.01;
//     double
// }


