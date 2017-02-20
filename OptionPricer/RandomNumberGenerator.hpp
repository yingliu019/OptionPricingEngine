//
//  RandomNumberGenerator.hpp
//  OptionPricer
//
//  Created by 刘颖 on 1/24/17.
//  Copyright © 2017 刘颖. All rights reserved.
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
