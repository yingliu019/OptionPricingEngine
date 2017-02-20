//
//  BinomialTree.cpp
//  OptionPricer
//
//  Created by 刘颖 on 1/24/17.
//  Copyright © 2017 刘颖. All rights reserved.
//

#include <iostream>
#include <cmath>

#include "BinominalTree.hpp"
using namespace std;

BinomialTree::BinomialTree(const shared_ptr<StochasticProcess>& stochasticProcess, int steps)
    : stochasticProcess_(stochasticProcess),N_(steps),treeInitialized_(false) {
    double T = stochasticProcess_->GetMaturity();
    dt_ = T / N_;
    buildTree();
}

void BinomialTree::buildTree() {
    double S_0 = stochasticProcess_->GetInitialStock();
    double r = stochasticProcess_->GetInterestRate();
    double sigma = stochasticProcess_->GetVolatility();

    
    tree_.resize(N_ + 1);
    
    for (long i = 0; i <= N_; ++i) {
        tree_[i].resize(i + 1);
    }
    tree_[0][0].first = S_0;
    double nu = (r - 0.5*sigma*sigma);
    double sqrt_dt_ = sqrt(dt_);
    for (long i = 1; i <= N_; ++i) {
        tree_[i][0].first = tree_[i - 1][0].first * exp(nu * dt_ - sigma * sqrt_dt_);
        //cout << "this is for building bi tree" << i << 0 << " " << tree_[i][0].first << endl;
        for (int j = 1; j <= i; ++j) {
            tree_[i][j].first = tree_[i][0].first * exp(2 * j * sigma * sqrt_dt_);
            //cout << "this is for building bi tree" << i << j << " " << tree_[i][j].first << endl;
        }
        //cout << endl;
    }
    
    treeInitialized_ = true;
}

double BinomialTree::PriceForAmerican(const shared_ptr<Payoff>& payoff) {
    double r = stochasticProcess_->GetInterestRate();
    
    if (!treeInitialized_) buildTree();
    
    for (long ir = N_; ir >= 0; --ir) {
        for (long j = 0; j <= ir; ++j) {
            tree_[ir][j].second = payoff->expirationPayoff(tree_[ir][j].first);
        }
    }
    
    /*
     for (long i = 0; i <= N_; i++) {
     for (int j = -i, k = 0; j <= i; j += 2, k++) {
     cout << "if strike now " << i << k << " " << tree_[i][k].second << endl;
     }
     cout << endl;
     }
     */
    
    double disc = exp(-r * dt_);

    for (long ir = N_ - 1; ir >= 0; --ir) {
        for (long j = 0; j <= ir; ++j) {
            double discountedExpectation = disc * 0.5 * (tree_[ir + 1][j].second + tree_[ir + 1][j + 1].second);  //if hold
            tree_[ir][j].second = payoff->intermediatePayoff(tree_[ir][j].first, discountedExpectation);
        }
    }
    
    /*
     for (long i = 0; i <= N_; i++) {
     for (int j = -i, k = 0; j <= i; j += 2, k++) {
     cout << "final payoff" << i << k << " " << tree_[i][k].second << endl;
     }
     cout << endl;
     }
     */
    
    return tree_[0][0].second;
}


/*
 double BinomialTree::Delta(double K) {
	return 1.0;
 }
 */

double BinomialTree::PriceForEuropean(const shared_ptr<Payoff>& payoff) {
    
    double r = stochasticProcess_->GetInterestRate();
    
    if (!treeInitialized_) buildTree();
    
    for (long ir = N_; ir >= 0; --ir) {
        for (long j = 0; j <= ir; ++j) {
            tree_[ir][j].second = payoff->expirationPayoff(tree_[ir][j].first);
        }
    }
    
    double disc = exp(-r*dt_);
    
    if (payoff->knockCondition()) {
        double barrier = payoff->getBarrier();
        for (long ir = N_ - 1; ir >= 0; --ir) {
            for (long j = 0; j <= ir; ++j) {
                double discountedExpectation = disc * 0.5 * (tree_[ir + 1][j].second + tree_[ir + 1][j + 1].second);  //if hold
                tree_[ir][j].second = (tree_[ir][j].first >= barrier)? 0 : discountedExpectation;
            }
        }
    } else {
        for (long ir = N_ - 1; ir >= 0; --ir) {
            for (long j = 0; j <= ir; ++j) {
                double discountedExpectation = disc * 0.5 * (tree_[ir + 1][j].second + tree_[ir + 1][j + 1].second);  //if hold
                tree_[ir][j].second = discountedExpectation;
            }
        }
    }
    
    return tree_[0][0].second;
}
