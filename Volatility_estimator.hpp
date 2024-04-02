//
//  Volatility_estimator.hpp
//  Pricing Options
//
//  Created by Marama on 29/12/2023.
//

#pragma once

#include <vector>
#include <string>

class VolatilityEstimator {
private:
    std::vector<double> prices; //historical prices that we study

public:
    //constructor
    VolatilityEstimator(const std::string filename);
    
    //methods
    std::string readTextFile(const std::string filename); //takes filename as input and returns a string containing the prices
    std::vector<double> readStockPrices(const std::string filename); //takes filename and returns the vector of prices
    double calculateVolatility() const; //calculates the estimator of volatility
    
};

