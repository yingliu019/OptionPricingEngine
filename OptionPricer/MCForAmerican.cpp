//
//  MCForAmerican.cpp
//  OptionPricer
//
//  Created by YingLiu on 1/25/17.
//  Copyright © 2017 YingLiu. All rights reserved.
//


#include "MCForAmerican.hpp"

#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <algorithm>
#include <iomanip>
#include <cassert>
#include <string>

using namespace std;
using namespace Eigen;

MCForAmerican::MCForAmerican(const shared_ptr<StochasticProcess>& stochasticProcess, double paths, double steps)
: stochasticProcess_(stochasticProcess), paths_(paths), steps_(steps), initialized_(false) {
    buildGrid();
}


void MCForAmerican::buildGrid() {
    double S_0 = stochasticProcess_->GetInitialStock();
    double r = stochasticProcess_->GetInterestRate();
    double sigma = stochasticProcess_->GetVolatility();
    double T = stochasticProcess_->GetMaturity() / steps_;
    
    
    nodes_.resize(paths_);
    
    RandomNumberGenerator gen;
    gen.SetSeed();
    
    for (int i = 0; i < paths_; ++i) {
        
        nodes_[i].resize(steps_);
        nodes_[i][0].S = S_0;
        
        for (int j = 1; j < steps_; ++j) {
            double z = gen.RandomByBoxMuller();
            nodes_[i][j].S = nodes_[i][j].S * exp((r - sigma * sigma / 2.0) * T + sigma * z * sqrt(T));
        }
    }
    initialized_ = true;
}


double MCForAmerican::PriceForAmerican(const shared_ptr<Payoff>& payoff) {    //只写了put
    
    if (!initialized_) buildGrid();
    
    double K = payoff->GetK();
    double r = stochasticProcess_->GetInterestRate();
    double T = stochasticProcess_->GetMaturity() / steps_;
    double disc = exp(-r * T);
    
    bool flag = payoff->knockCondition();
    assert(flag != true && "not recommend use MC for barrier");
    
    
    for (int i = 0; i < paths_; ++i) {
        if (nodes_[i][steps_ - 1].S < K) {
            nodes_[i][steps_ - 1].immEx = std::max(K - nodes_[i][steps_ - 1].S, 0.0);
            nodes_[i][steps_ - 1].early = true;
        } else {
            nodes_[i][steps_ - 1].immEx = 0.0;
            nodes_[i][steps_ - 1].early = false;
        }
        nodes_[i][steps_ - 1].value = nodes_[i][steps_ - 1].immEx;
    }
    
    double runningSum = 0.0;
    for (int t = steps_ - 2; t >= 0; --t) {
        vector<double> tempS;     //stock price now
        for (int i = 0; i < paths_; ++i) {
            if (nodes_[i][t].S < K) {
                nodes_[i][t].immEx = std::max(K - nodes_[i][t].S, 0.0);
                tempS.push_back(nodes_[i][t].S);
            } else {
                // we don't regress OTM part
                nodes_[i][t].immEx = 0.0;
            }
        }
        
        // begin regression
        long size = tempS.size();
        VectorXd points(size);  //option price if strike at next period
        int index = 0;
        
        for (int i = 0; i < paths_; ++i) {
            if (nodes_[i][t].S < K) {
                //points[index] = nodes_[i][t + 1].immEx * disc;
                points[index] = nodes_[i][t + 1].value * disc;
                index += 1;
            }
        }
        
        MatrixXd B(size, 3);
        for (int i = 0; i < size; ++i) {
            B(i, 0) = 1.0;
            B(i, 1) = tempS[i];
            B(i, 2) = tempS[i] * tempS[i];
        }
        
        // regression coefficient
        VectorXd x = B.jacobiSvd(ComputeThinU | ComputeThinV).solve(points);
        
        for (int i = 0; i < paths_; ++i) {
            if (nodes_[i][t].S < K) {
                
                double S = nodes_[i][t].S;
                
                nodes_[i][t].contEx = x[0] + x[1] * S + x[2] * S * S;
                nodes_[i][t].early = nodes_[i][t].immEx > nodes_[i][t].contEx ? true : false;
                
                if (nodes_[i][t].early) {
                    nodes_[i][t].value = nodes_[i][t].immEx;
                    nodes_[i][t + 1].immEx = 0.0;
                    nodes_[i][t + 1].early = false;
                } else {
                    //nodes_[i][t].contEx = nodes_[i][t + 1].value * disc;    可要可不要？
                    nodes_[i][t].value = nodes_[i][t].contEx;
                    //nodes_[i][t].immEx = 0.0;
                }
            } else {
                nodes_[i][t].early = false;
                //nodes_[i][t].contEx = nodes_[i][t + 1].value * disc;
                nodes_[i][t].value = nodes_[i][t].contEx;
            }
            
            if (t == 0) {
                runningSum += nodes_[i][t].value;
            }
        }
    }
    
    return runningSum / paths_;
}

double MCForAmerican::PriceForEuropean(const shared_ptr<Payoff>& payoff) {
    double price = -101;
    assert(price != -101  && "MC American Pricer is not for European Option");
    return -101;
}






 
