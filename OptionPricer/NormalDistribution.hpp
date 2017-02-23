//
//  NormalDistribution.hpp
//  OptionPricer
//
//  Created by YingLiu on 2/10/17.
//  Copyright © 2017 YingLiu. All rights reserved.
//

#ifndef NormalDistribution_hpp
#define NormalDistribution_hpp

#include <stdio.h>

class NormalUtils
{
public:
    NormalUtils(double x);
    
    double NormCdf(double x);
    double NormPdf(double x);
    
};

#endif /* NormalDistribution_hpp */
