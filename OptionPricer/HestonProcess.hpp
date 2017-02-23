//
//  HestonProcess.hpp
//  OptionPricer
//
//  Created by YingLiu on 2/9/17.
//  Copyright © 2017 YingLiu. All rights reserved.
//

#ifndef HestonProcess_hpp
#define HestonProcess_hpp

#include <stdio.h>

#include "StochasticProcess.hpp"

class HestonProcess : public StochasticProcess
{
public:
    HestonProcess(double S0, double V0, double T, double r, double q,
                  double kappa, double theta, double eta, double rho)
    : S0_(S0), V0_(V0), T_(T), r_(r), q_(0),
    kappa_(kappa), theta_(theta), eta_(eta), rho_(rho)
    {}
    
    double S0_;
    double T_;
    double r_;
    double q_;
    
    double V0_;
    double kappa_;
    double theta_;
    double eta_;
    double rho_;
};

#endif /* HestonProcess_hpp */

// home work, 6.2 cmc for heston
// and 8
