
//  NaiveMC.hpp
//  OptionPricer
//
//  Created by YingLiu on 1/25/17.
//  Copyright © 2017 YingLiu. All rights reserved.
//


#ifndef OrdinaryMC_hpp
#define OrdinaryMC_hpp

#include <stdio.h>
#include "MCForEuropean.hpp"

#include <vector>
#include <iostream>
#include <utility>



using namespace std;

class OrdinaryMC : public MCForEuropean {
    
public:
    OrdinaryMC(const shared_ptr<StochasticProcess>& stochasticProcess, double paths);
    
    double PriceForEuropean(const shared_ptr<Payoff>& payoff);
    double PriceForAmerican(const shared_ptr<Payoff>& payoff);
    
    //double Delta(double K);
    
};

#endif /* OrdinaryMC_hpp */
