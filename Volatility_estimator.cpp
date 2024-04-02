//
//  Volatility_estimator.cpp
//  Pricing Options
//
//  Created by Marama on 29/12/2023.
//

#include "Volatility_estimator.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>

VolatilityEstimator::VolatilityEstimator(const std::string filename) {
    prices = readStockPrices(filename);
}

//this function reads the txt file and returns a std::string, we will need it for the readStockPrices function
std::string VolatilityEstimator::readTextFile(const std::string filename) {
    
    std::ifstream file(filename);
    std::string fileContent;
    std::string line;

    //we check if the file is open or not
    if (file.is_open()) {
        
        //if it is open, we add each line of the txt file to the string
        while (std::getline(file, line)) {
            fileContent += line + "\n";
        }
        file.close();
    } else {
        std::cerr << "Opening error of file : " << filename << std::endl;
    }

    return fileContent;
}

//this function calls readTextFile which returns a string, then readStockPrices converts this string into a vector of doubles
std::vector<double> VolatilityEstimator::readStockPrices(const std::string filename) {
    
    //we call readTextFile to convert txt file into a string
    std::string file = VolatilityEstimator::readTextFile(filename);
    
    std::vector<double> priceHistoric;
    std::stringstream ss(file);
    std::string price;

    while (std::getline(ss, price, ',')) { 
        // we use ',' as the deliminator because prices of the string are separated by ','
        
        priceHistoric.push_back(std::stod(price)); 
        // we convert price into a double and we add it to the vector
    }
    
    return priceHistoric;
}

    

    

double VolatilityEstimator::calculateVolatility() const {
    
    int size = static_cast<int>((prices.size()));
    double sumReturns = 0.0;
    double averageReturns = 0.0;

    // calculating logarithmic returns
    std::vector<double> returns;
    for (int i = 1; i < size; ++i) {
        double returnVal = log(prices[i] / prices[i - 1]);
        returns.push_back(returnVal);
        sumReturns += returnVal;
    }

    // calculating average returns
    averageReturns = sumReturns / (size - 1);

    // calculating variance
    double sumSquaredDiffs = 0.0;
    for (int i = 0; i < size - 1; ++i) {
        sumSquaredDiffs += pow(returns[i] - averageReturns, 2);
    }
    double variance = sumSquaredDiffs / (size - 2);

    // calculating volatility as the standard deviation
    double volatility = sqrt(variance);

    return volatility;
}



