//
//  StochasticProcess.hpp
//  OptionPricer
//
//  Created by YingLiu on 2/11/17.
//  Copyright © 2017 YingLiu. All rights reserved.
//

#ifndef StochasticProcess_hpp
#define StochasticProcess_hpp

#include <stdio.h>


class StochasticProcess {
    
public:
    StochasticProcess()
    {}
    
    
    virtual double GetInitialStock() const = 0;
    virtual double GetInterestRate() const = 0;
    virtual double GetDividend() const = 0;
    virtual double GetVolatility() const = 0;
    virtual double GetMaturity() const = 0;
     
    /*
    double GetInitialStock();
    double GetInterestRate();
    double GetDividend();
    double GetVolatility();
    double GetMaturity();
     */
};



#endif /* StochasticProcess_hpp */
