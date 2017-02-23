//
//  MCForAmerican.hpp
//  OptionPricer
//
//  Created by YingLiu on 1/25/17.
//  Copyright © 2017 YingLiu. All rights reserved.
//



#ifndef MCForAmerican_hpp
#define MCForAmerican_hpp

#include <stdio.h>
#include <vector>

#include "PricingEngine.hpp"
#include "RandomNumberGenerator.hpp"
#include <cmath>

using namespace std;

class MCForAmerican : public PricingEngine {
    
public:
    MCForAmerican(const shared_ptr<StochasticProcess>& stochasticProcess, double paths, double steps);
    
    double PriceForAmerican(const shared_ptr<Payoff>& payoff);
    double PriceForEuropean(const shared_ptr<Payoff>& payoff);
    
    //double Delta(double K);
    
protected:
    void buildGrid();
    
    unsigned int paths_;
    double steps_;
    bool initialized_;
    
    shared_ptr<StochasticProcess> stochasticProcess_;
    
    struct Node
    {
        double S;
        double immEx;  // immediate exercise
        double contEx;// if hold, payoff
        bool early;
        double value;
    };
   
    vector<vector<Node>> nodes_;

    double dt_;
};

#endif /* MCForAmerican_hpp */





