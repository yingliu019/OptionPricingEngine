
#ifndef FDBase_hpp
#define FDBase_hpp

#include <stdio.h>

#include "PricingEngine.hpp"

#include <vector>
//#include "BSPDE.h"

using std::vector;


class FDBase : public PricingEngine {

public:
    FDBase(int J, int N, const shared_ptr<StochasticProcess>& stochasticProcess)
    : NJ_(2 * J + 1), J_(J), N_(N), stochasticProcess_(stochasticProcess), initialized_(false)
    {}
    
    virtual double PriceForAmerican(const shared_ptr<Payoff>& payoff) = 0;
    virtual double PriceForEuropean(const shared_ptr<Payoff>& payoff) = 0;
    
protected: 
    int NJ_;  // node vertical total
    int N_;   // node horizental total
    int J_;   // node half vertical
    //double T_;
    //BlackScholesPDE pde_;
    shared_ptr<StochasticProcess> stochasticProcess_;
    
    double dx_;
    double dt_;
    
    //vector<double> St_;  //stock price
    typedef vector<double> VerticalNodes;
    typedef vector<VerticalNodes> Grid;
    Grid grid_;    // vector<vector<double>> grid; // [N + 1][NJ];
    
    virtual void initializedGrid() = 0;
    virtual void boundaryConditions(double K) = 0;
    
    bool initialized_;
    
};

#endif /* FDBase_hpp */


