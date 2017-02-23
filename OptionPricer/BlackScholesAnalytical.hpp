//
//  BlackScholes.hpp
//  OptionPricer
//
//  Created by YingLiu on 2/10/17.
//  Copyright © 2017 YingLiu. All rights reserved.
//

#ifndef BlackScholesAnalytical_hpp
#define BlackScholesAnalytical_hpp

#include <stdio.h>
#include "NormalDistribution.hpp"
#include "PricingEngine.hpp"


class BlackScholesAnalytical : public PricingEngine {
    
public:
    BlackScholesAnalytical(const shared_ptr<StochasticProcess>& stochasticProcess, double K);
    
    void SetNormalUtils(double d);
    
    double PriceForAmerican(const shared_ptr<Payoff>& payoff);
    double PriceForEuropean(const shared_ptr<Payoff>& payoff);
    //double Delta(const shared_ptr<Payoff>& payoff);
    //double Gamma(const shared_ptr<Payoff>& payoff);


protected:
    shared_ptr<StochasticProcess> stochasticProcess_;
    NormalUtils NormalUtils_;
    double K_;
};

#endif /* BlackScholesAnalytical_hpp */






