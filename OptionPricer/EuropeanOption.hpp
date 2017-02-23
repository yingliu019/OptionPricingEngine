//
//  EuropeanOption.hpp
//  OptionPricer
//
//  Created by YingLiu on 1/24/17.
//  Copyright © 2017 YingLiu. All rights reserved.
//

#ifndef EuropeanOption_hpp
#define EuropeanOption_hpp

#include <stdio.h>

#include"Option.hpp"

class EuropeanOption : public Option {

public:
    EuropeanOption(const shared_ptr<Payoff>& payoff);
    
    double Price();
    
};

#endif /* EuropeanOption_hpp */
