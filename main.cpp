//
//  main.cpp
//  Pricing Options
//
//  Created by Marama on 29/12/2023.
//

#include <iostream>
#include "Options.hpp"
#include "Monte_Carlo.hpp"
#include "Options.hpp"
#include "Binomial.hpp"
#include "Volatility_estimator.hpp"
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <fstream>

using namespace std;


void test1() // Test for a call option
{
    
    // The idea here is to make a test of our code for an option with Apple stock as the underlying asset. We suppose that there are no dividends.
    
    int type = 1;  // This is a CALL option
    double r = 4.73/100;   // We took the risk free rate of the US for a maturity of 1 Year (since our option maturity is 1 Year)
    double K = 220;   // Strike price at 220
    double T = 1;  // Maturity is one year
    double sigma = 0.126299;  // We compute the volatility
    double S0 = 200;  // Current price of the stock
    
    Option o = Option(type, r,  K,  T,  sigma,  S0);
    o.output();
    

    European_Option_Binomial B = European_Option_Binomial();
    
    int a = 20;
    
    cout << "The price of the option with a multiple steps Binomial method is :" << endl;
    cout << B.Binomial_Method_Price_option_steps(o, a)<< endl;
    
    
    Monte_Carlo_Simulation M = Monte_Carlo_Simulation();
    
    cout << "The price of the option with the Monte Carlo method is :" << endl;
    cout << M.Monte_Carlo_Simulation_Price(o)<< endl;
}


void test2()  // Test for a put option
{
    // The idea here is to make a test of our code for an option with Apple stock as the underlying asset. We suppose that there are no dividends.
    
    int type = -1;  // This is a PUT option
    double r = 4.73/100;   // We took the risk free rate of the US for a maturity of 1 Year (since our option maturity is 1 Year)
    double K = 220;   // Strike price at 220
    double T = 1;  // Maturity is one year
    double sigma = 0.126299;  // We compute the volatility
    double S0 = 200;  // Current price of the stock
    
    Option o = Option(type, r,  K,  T,  sigma,  S0);
    o.output();
    

    European_Option_Binomial B = European_Option_Binomial();
    
    int a = 20;
    
    cout << "The price of the option with a multiple steps Binomial method is :" << endl;
    cout << B.Binomial_Method_Price_option_steps(o, a)<< endl;
    
    
    Monte_Carlo_Simulation M = Monte_Carlo_Simulation();
    
    cout << "The price of the option with the Monte Carlo method is :" << endl;
    cout << M.Monte_Carlo_Simulation_Price(o)<< endl;

}




int main() {
    //the following instructions are meant to estimate the volatility of the underlying asset
    std::string filename = "/Users/marama/Desktop/HistoricalAPPL.txt";
    //you have to download the txt file "HistoricalAPPL.txt" first and then replace filename by the path to this file on your computer
    VolatilityEstimator estimator(filename);
    double volatility = estimator.calculateVolatility();
    std::cout << "Estimated volatility: " << volatility << std::endl;
    
    //those are tests for call and put options
    test1();
    //test2();
}

