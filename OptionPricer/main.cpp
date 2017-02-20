#include "BinaryCallPayoff.hpp"
#include "BinaryPutPayoff.hpp"
#include "CallPayoff.hpp"
#include "PutPayoff.hpp"
#include "EuropeanOption.hpp"
#include "AmericanOption.hpp"
#include "BinominalTree.hpp"
#include "TrinominalTree.hpp"
#include "FDExplicit.hpp"
#include "OrdinaryMC.hpp"
#include "BlackScholesAnalytical.hpp"
#include "StochasticProcess.hpp"
#include "BlackScholesProcess.hpp"
#include "UpAndOutPutPayoff.hpp"

#include <iostream>

using namespace std;

int main() {
    
    //basic parameters
    double S0 = 100;
    double sigma = 0.5;
    double r = 0.1;
    double T = 0.5;
    double K = 110;
    double q = 0;
    double H = 114;
    
    const int N = 3.0;
    const double paths = 3.0;
    int J = 3;

    shared_ptr<Payoff> putPayoff = std::make_shared<PutPayoff>(K);
    shared_ptr<Payoff> callPayoff = make_shared<CallPayoff>(K);

    
    // 1. create the option
    EuropeanOption europeanPut(putPayoff);
    EuropeanOption europeanCall(callPayoff);
    AmericanOption americanPut(putPayoff);
    
    // 2. create the model parameters
    shared_ptr<StochasticProcess> bsProcess = std::make_shared<BlackScholesProcess>(S0, r, q, sigma, T);
    
    // 3. create the pricer
    shared_ptr<PricingEngine> bs = std::make_shared<BlackScholesAnalytical>(bsProcess, K);
    shared_ptr<PricingEngine> triTreePricer = std::make_shared<TrinomialTree>(bsProcess, N);
    shared_ptr<PricingEngine> fdPricer = std::make_shared<FDExplicit>(J, N, bsProcess);
    shared_ptr<PricingEngine> mcPricer = std::make_shared<OrdinaryMC>(bsProcess, paths);

    
    // 4. price
    shared_ptr<Payoff> upAndOut = std::make_shared<UpAndOutPutPayoff>(K, H);
    europeanPut.SetpricingEngine(mcPricer);
    cout << "Trinominal Tree -- Euro Put Value: " << europeanPut.Price() << endl;
    
    
    americanPut.SetpricingEngine(triTreePricer);
    double price = americanPut.Price();
    cout << "American Put Value: " << price << endl;
    
    europeanPut.SetpricingEngine(bs);
    cout << "BS Analytical --- Euro Put Value: " << europeanPut.Price() << endl;
    
    europeanPut.SetpricingEngine(triTreePricer);
    cout << "Trinominal Tree -- Euro Put Value: " << europeanPut.Price() << endl;
    
    europeanPut.SetpricingEngine(fdPricer);
    cout << "Finite Difference -- Euro Put Value: " << europeanPut.Price() << endl;
    
    europeanPut.SetpricingEngine(mcPricer);
    cout << "MC --- Euro Put Value: " << europeanPut.Price() << endl;

}
