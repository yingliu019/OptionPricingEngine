//
//  TrinominalTree.hpp
//  OptionPricer
//
//  Created by YingLiu on 1/24/17.
//  Copyright © 2017 YingLiu. All rights reserved.
//

#ifndef TrinominalTree_hpp
#define TrinominalTree_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <utility>

#include "PricingEngine.hpp"


class TrinomialTree : public PricingEngine {
    
public:
    TrinomialTree(const shared_ptr<StochasticProcess>& stochasticProcess, double steps);
    double PriceForAmerican(const shared_ptr<Payoff>& payoff);
    double PriceForEuropean(const shared_ptr<Payoff>& payoff);
    //double Delta(double K);
    
private:
    void buildTree();
    bool treeInitialized_;
    
    typedef double StockPrice;
    typedef double OptionPrice;
    typedef std::pair<StockPrice, OptionPrice> Node;
    typedef std::vector<Node> VerticalNodes;
    typedef std::vector<VerticalNodes> Tree;
    
    Tree tree_;
    shared_ptr<StochasticProcess> stochasticProcess_;
    double N_;
    double dt_;
};


#endif /* TrinominalTree_hpp */







