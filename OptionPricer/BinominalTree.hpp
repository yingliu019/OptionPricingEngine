//
//  BinomialTree.hpp
//  OptionPricer
//
//  Created by 刘颖 on 1/24/17.
//  Copyright © 2017 刘颖. All rights reserved.
//

#ifndef BinomialTree_hpp
#define BinomialTree_hpp

#include <stdio.h>

#include <string>
#include <vector>
#include <utility>

#include "PricingEngine.hpp"

class BinomialTree : public PricingEngine {
    
public:
    BinomialTree(const shared_ptr<StochasticProcess>& stochasticProcess, int steps);
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
    typedef std::vector<VerticalNodes> Tree;     //vector's vector
    
    Tree tree_;
    shared_ptr<StochasticProcess> stochasticProcess_;
    int N_;
    double dt_;
};

#endif /* BinomialTree_hpp */

