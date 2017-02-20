//
//  EuropeanOption.hpp
//  OptionPricer
//
//  Created by 刘颖 on 1/24/17.
//  Copyright © 2017 刘颖. All rights reserved.
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
