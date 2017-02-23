//
//  NormalDistribution.cpp
//  OptionPricer
//
//  Created by YingLiu on 2/10/17.
//  Copyright © 2017 YingLiu. All rights reserved.
//

#include "NormalDistribution.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

NormalUtils::NormalUtils(double x)
{}

double NormalUtils::NormCdf(double x)
{
    const double b1 = 0.319381530;
    const double b2 = -0.356563782;
    const double b3 = 1.781477937;
    const double b4 = -1.821255978;
    const double b5 = 1.330274429;
    const double p = 0.2316419;
    const double c = 0.39894228;
    
    double normCdf_ = 0.0;
    if (x >= 0.0)
    {
        double t = 1.0 / (1.0 + p * x);
        normCdf_ = (1.0 - c * exp(-x * x / 2.0) * t * (t *(t * (t * (t * b5 + b4) + b3) + b2) + b1));
    }
    else
    {
        double t = 1.0 / (1.0 - p * x);
        normCdf_ = (c * exp(-x * x / 2.0) * t * (t *(t * (t * (t * b5 + b4) + b3) + b2) + b1));
    }
    return normCdf_;
};

double NormalUtils::NormPdf(double x)
{
    double normPdf_ = exp(-x * x / 2.0) / sqrt(2 * M_PI);
    return normPdf_;
    
}
