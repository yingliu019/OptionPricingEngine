
# include "FDExplicit.hpp"
# include<iostream>
# include <cmath>
#include <cassert>
#include <string>

using namespace std;

FDExplicit::FDExplicit(int J, int N, const shared_ptr<StochasticProcess>& stochasticProcess)
: FDBase(J, N, stochasticProcess)
{
    double sigma = stochasticProcess_->GetVolatility();
    double T = stochasticProcess_->GetMaturity();
    
    dt_ = T / N_;
    dx_ = sigma * sqrt(3 * dt_);
    initializedGrid();
}

void FDExplicit::initializedGrid() {

    grid_.resize(N_ + 1);
    
    for (long i = 0; i <= N_; ++i) {
        grid_[i].resize(NJ_);
    }
    
    initialized_ = true;
   
}

void FDExplicit::boundaryConditions(double K) {
    double S_0 = stochasticProcess_->GetInitialStock();

    xMax_ = log(S_0) + J_ * dx_; // and it's upper bound
    xMin_ = log(S_0) - J_ * dx_; // and it's lower bound
    //sMax_ = exp(xMax_);
    //sMin_ = exp(xMin_);
    // S_lowboundary is S_{-J} for CN FD
    // now we haven't use K as boundray condition
}


double FDExplicit::PriceForEuropean(const shared_ptr<Payoff>& payoff) {
    
    if (!initialized_) initializedGrid();
    
    bool flag = payoff->knockCondition();
    assert(flag != true && "not recommend use FD for barrier");
    
    double K = payoff->GetK();
    boundaryConditions(K);

    double r = stochasticProcess_->GetInterestRate();
    double sigma = stochasticProcess_->GetVolatility();
    double q =  stochasticProcess_->GetDividend();
    
    double nu_ = r - q - 0.5 * sigma * sigma;
    double qu = 0.5 * dt_ * ((sigma / dx_) * (sigma / dx_) + nu_ / dx_);
    double qm = 1.0 - dt_ * (sigma / dx_) * (sigma / dx_);
    double qd = 0.5 * dt_ * ((sigma / dx_) * (sigma / dx_) - nu_ / dx_);
    
    grid_[N_][0] = payoff->expirationPayoff(exp(xMin_));   // assert put(smin) big enough and call(smin)=0
    for (int j = 1; j < NJ_; j++) {
        grid_[N_][j] = payoff->expirationPayoff(exp(xMin_ + j * dx_));
    }
    
    double disc = exp(-r * dt_);
    for (int i = N_ - 1; i >= 0; --i) {
        for (int j = 1; j < NJ_ - 1; ++j) {
            grid_[i][j] = disc * (qd * grid_[i + 1][j + 1] + qm * grid_[i + 1][j] + qu * grid_[i + 1][j - 1]);
        }
    }
    return grid_[0][J_];
}

double FDExplicit::PriceForAmerican(const shared_ptr<Payoff>& payoff) {
    double price = -101;
    assert(price != -101  && "FD Explicit Pricer is not for American Option");
    return -101;
}








 

