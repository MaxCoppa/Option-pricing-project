//
//  Options.hpp
//  Pricing Options
//
//  Created by Marama on 29/12/2023.
//

#pragma once

#include <iostream>

class Option {

private:
    int type;       // Type of the option
    double r;       // Risk-free rate
    double K;       // Strike price of the option
    double T;       // Expiry date of the option
    double sigma;   // Volatility of the underlying asset
    double S0;      // Initial price of the underlying asset

public:

    // Constructors and destructor
    Option();   // Default constructor
    Option(int type, double r, double K, double T, double sigma, double S0);   // Parameterized constructor
    ~Option() {}   // Destructor

    // Accessor methods
    int Get_type() const;   // Get the type of the option
    double Get_risk_free_rate() const;   // Get the risk-free rate
    double Get_strike_price() const;   // Get the strike price
    double Get_expiry_date() const;   // Get the expiry date
    double Get_volatility() const;   // Get the volatility
    double Get_initial_price() const;   // Get the initial price

    // Modification methods
    void Set_type(bool);   // Modify the type of the option
    void Set_risk_free_rate(double);   // Modify the risk-free rate
    void Set_strike_price(double);   // Modify the strike price
    void Set_expiry_date(double);   // Modify the expiry date
    void Set_initial_price(double);   // Modify the initial price

    // Display method
    void output() const;   // Display information about the option
};

