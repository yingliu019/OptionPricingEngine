//
//  NaiveMC.cpp
//  OptionPricer
//
//  Created by YingLiu on 1/25/17.
//  Copyright © 2017 YingLiu. All rights reserved.
//


#include "ImportanceSamplingMC.hpp"
#include "RandomNumberGenerator.hpp"

#include <cmath>

using namespace std;

ImportanceSamplingMC::ImportanceSamplingMC(const shared_ptr<StochasticProcess>& stochasticProcess, double paths)
: MCForEuropean(stochasticProcess, paths), NormalUtils_(0.0)
{}


double ImportanceSamplingMC::PriceForEuropean(const shared_ptr<Payoff>& payoff) {
    double S_0 = stochasticProcess_->GetInitialStock();
    double r = stochasticProcess_->GetInterestRate();
    double sigma = stochasticProcess_->GetVolatility();
    double T = stochasticProcess_->GetMaturity();
    double q =  stochasticProcess_->GetDividend();
    double K = payoff->GetK();

    bool flag = payoff->knockCondition();
    assert(flag != true && "not recommend use MC for barrier");
    
    //目前只写了 vanilla call 对gbm process
    double F = S_0 * exp((r - q)* T);
    double d_1 = (log(F) - log(K)) / (sigma * sqrt(T)) + sigma * sqrt(T) / 2;
    double d_2 = (log(F) - log(K)) / (sigma * sqrt(T)) - sigma * sqrt(T) / 2;
    double S_T_1 = (NormalUtils_.NormCdf(d_1) * F - NormalUtils_.NormCdf(d_2) * K) * exp(-r * T);
    
    double r_updated = r + sigma * sigma;
    double F_updated = S_0 * exp((r_updated - q)* T);
    double d_1_updated = (log(F_updated) - log(K)) / (sigma * sqrt(T)) + sigma * sqrt(T) / 2;
    double d_2_updated = (log(F_updated) - log(K)) / (sigma * sqrt(T)) - sigma * sqrt(T) / 2;
    double S_T_2 = (NormalUtils_.NormCdf(d_1_updated) * F - NormalUtils_.NormCdf(d_2_updated) * K) * exp(-r_updated * T);
    
    double S_bar = S_0 * S_T_2 / S_T_1;
    double lambda = (log(S_bar) - log(S_0)) / (T * sigma) - r / sigma;

    
    RandomNumberGenerator gen;
    gen.SetSeed();
    
    double runningSum = 0.0;
    
    for (unsigned int i = 0; i < paths_; i++) {
        double z = gen.RandomByBoxMuller();
        double S_T = S_0 * exp((r + lambda * sigma - sigma * sigma / 2.0) * T + sigma * z * sqrt(T));
        double P_temp = payoff->expirationPayoff(S_T);
        double P = P_temp * exp((-lambda) * z - 0.5 * lambda * lambda * T);
        
        runningSum += P;
    }
    return exp(-r*T) * (runningSum / paths_);
}

double ImportanceSamplingMC::PriceForAmerican(const shared_ptr<Payoff>& payoff) {
    double price = -101;
    assert(price != -101  && "Importance Sampling MC Pricer is not for American Option");
    return -101;
}




