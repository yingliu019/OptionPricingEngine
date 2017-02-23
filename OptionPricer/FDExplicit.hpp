//
//  FDExplicit.hpp
//  OptionPricer
//
//  Created by YingLiu on 1/24/17.
//  Copyright © 2017 YingLiu. All rights reserved.
//

#ifndef FDExplicit_hpp
#define FDExplicit_hpp


#include <stdio.h>
//#include <vector>
#include <iostream>
#include <utility>

#include "FDBase.hpp"

using namespace std;


class FDExplicit : public FDBase {

public:
    FDExplicit(int J, int N, const shared_ptr<StochasticProcess>& stochasticProcess);
    
    double PriceForEuropean(const shared_ptr<Payoff>& payoff);
    double PriceForAmerican(const shared_ptr<Payoff>& payoff);
    
    //double Delta(double K);
    
protected:
    void initializedGrid();
    void boundaryConditions(double K);
    
private:
    double xMax_;
    double xMin_;
    
};


#endif /* FDExplicit_hpp */





