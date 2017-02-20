//
//  BlackScholesProcess.hpp
//  OptionPricer
//
//  Created by 刘颖 on 1/24/17.
//  Copyright © 2017 刘颖. All rights reserved.
//

#ifndef BlackScholesProcess_hpp
#define BlackScholesProcess_hpp

#include <stdio.h>
#include "StochasticProcess.hpp"

class BlackScholesProcess : public StochasticProcess {
    
public:
    BlackScholesProcess(double S, double rate, double div, double vol, double expiry);
    
    double GetInitialStock() const;
    double GetInterestRate() const;
    double GetDividend() const;
    double GetVolatility() const;
    double GetMaturity() const;


private:
    double S0_;
    double r_;
    double q_;
    double sigma_;
    double T_;
    
    //BSPDE()
};

#endif /* BlackScholesProcess_hpp */
