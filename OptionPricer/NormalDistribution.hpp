//
//  NormalDistribution.hpp
//  OptionPricer
//
//  Created by 刘颖 on 2/10/17.
//  Copyright © 2017 刘颖. All rights reserved.
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
