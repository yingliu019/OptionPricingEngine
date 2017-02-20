//
//  AmericanOption.hpp
//  OptionPricer
//
//  Created by 刘颖 on 1/24/17.
//  Copyright © 2017 刘颖. All rights reserved.
//

#ifndef AmericanOption_hpp
#define AmericanOption_hpp

#include <stdio.h>

#include "Option.hpp"

using std::string;

class AmericanOption : public Option {
    
public:
    AmericanOption(const shared_ptr<Payoff>& payoff);
    double Price();
};

#endif /* AmericanOption_hpp */
