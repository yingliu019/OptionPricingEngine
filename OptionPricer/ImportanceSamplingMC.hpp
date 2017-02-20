//
//  ImportanceSamplingMC.hpp
//  OptionPricer
//
//  Created by 刘颖 on 2/10/17.
//  Copyright © 2017 刘颖. All rights reserved.
//

//suppose you wanted to price a deep OTM option under an intractable stochastic volatility model,
//using importance sampling.


#ifndef ImportanceSamplingMC_hpp
#define ImportanceSamplingMC_hpp

#include <stdio.h>
#include "MCForEuropean.hpp"
#include "NormalDistribution.hpp"

#include <vector>
#include <iostream>
#include <utility>



using namespace std;

class ImportanceSamplingMC : public MCForEuropean {
    
public:
    ImportanceSamplingMC(const shared_ptr<StochasticProcess>& stochasticProcess, double paths);
    
    double PriceForEuropean(const shared_ptr<Payoff>& payoff);
    double PriceForAmerican(const shared_ptr<Payoff>& payoff);
    
    //double Delta(double K);
    
private:
    NormalUtils NormalUtils_;
};

#endif /* ImportanceSamplingMC_hpp */
