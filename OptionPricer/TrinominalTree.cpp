//
//  TrinominalTree.cpp
//  OptionPricer
//
//  Created by 刘颖 on 1/24/17.
//  Copyright © 2017 刘颖. All rights reserved.
//

#include <iostream>
#include <cmath>

#include <cassert>
#include <string>

#include "TrinominalTree.hpp"
using namespace std;

TrinomialTree::TrinomialTree(const shared_ptr<StochasticProcess>& stochasticProcess, double steps)
    : stochasticProcess_(stochasticProcess),N_(steps),treeInitialized_(false) {
    double T = stochasticProcess_->GetMaturity();

    dt_ = T / N_;
    buildTree();
}

void TrinomialTree::buildTree() {

    double S_0 = stochasticProcess_->GetInitialStock();
    double sigma = stochasticProcess_->GetVolatility();
    double dx_ = sigma * sqrt(3 * dt_);
    
    tree_.resize(N_ + 1);
    for (long i = 0; i <= N_; ++i) {
        tree_[i].resize(2 * i + 1);
    }
    
    tree_[0][0].first = S_0;
    
    for (long i = 1; i <= N_; ++i) {
        tree_[i][0].first = tree_[i - 1][0].first * exp(-dx_);
        //cout << "this is for building tri tree" << i << "0" << " " << tree_[i][0].first << endl;
        for (int j = 1; j <= 2 * i; ++j) {
            tree_[i][j].first = tree_[i][0].first * exp(j * dx_);
            //cout << "this is for building tri tree" << i << j << " " << tree_[i][j].first << endl;
        }
         //cout << endl;
    }
    
    treeInitialized_ = true;
}

double TrinomialTree::PriceForAmerican(const shared_ptr<Payoff>& payoff) {
    double price = -101;
    assert(price != -101  && "trinominal tree Pricer is not for American Option");
    return -101;
}


/*
 double BinomialTree::Delta(double K) {
	return 1.0;
 }
 */

double TrinomialTree::PriceForEuropean(const shared_ptr<Payoff>& payoff) {

    double r = stochasticProcess_->GetInterestRate();
    double sigma = stochasticProcess_->GetVolatility();

    double nu = (r - 0.5* sigma * sigma);
    double dx_ = sigma * sqrt(3 * dt_);
    
    double Pu= 0.5*((sigma * sigma * dt_ + nu * nu * dt_ * dt_)/(dx_ * dx_)+((nu * dt_)/dx_));
    double Pd= 0.5*((sigma * sigma * dt_ + nu * nu * dt_ * dt_)/(dx_ * dx_)-((nu * dt_)/dx_));
    double Pm= 1- ((sigma * sigma * dt_ + nu * nu * dt_ * dt_)/(dx_ * dx_));
    
    
    if (!treeInitialized_) buildTree();
    
    for (long ir = N_; ir >= 0; --ir) {
        for (long j = 0; j <= 2 * ir; ++j) {
            tree_[ir][j].second = payoff->expirationPayoff(tree_[ir][j].first);
        }
    }
    
    double disc = exp(-r * dt_);

    
    if (payoff->knockCondition()) {
        double barrier = payoff->getBarrier();
        
        for (long ir = N_ - 1; ir >= 0; --ir) {
            for (long j = 0; j <= 2 * ir; ++j) {
                double discountedExpectation = disc * (Pu * tree_[ir + 1][j + 2].second + Pm * tree_[ir + 1][j + 1].second
                                                       + Pd * tree_[ir + 1][j].second);
                tree_[ir][j].second = (tree_[ir][j].first >= barrier)? 0 : discountedExpectation;
            }
        }
    } else {
        for (long ir = N_ - 1; ir >= 0; --ir) {
            for (long j = 0; j <= 2 * ir; ++j) {
                double discountedExpectation = disc * (Pu * tree_[ir + 1][j + 2].second + Pm * tree_[ir + 1][j + 1].second
                                                       + Pd * tree_[ir + 1][j].second);
                tree_[ir][j].second = discountedExpectation;
            }
        }
    }
    
    return tree_[0][0].second;

}

// later add assert of: contract.observationinterval
//abs(interval/deltat-round(interval/deltat)) > 1e-12
//error('This value of N fails to place the observation dates in the tree')
