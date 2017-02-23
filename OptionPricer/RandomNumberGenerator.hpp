//
//  RandomNumberGenerator.hpp
//  OptionPricer
//
//  Created by YingLiu on 1/24/17.
//  Copyright © 2017 YingLiu. All rights reserved.
//

#ifndef RandomNumberGenerator_hpp
#define RandomNumberGenerator_hpp

#include <stdio.h>

class RandomNumberGenerator {
    
public:
    static void SetSeed();
    static double RandomByBoxMuller();
};

#endif /* RandomNumberGenerator_hpp */
