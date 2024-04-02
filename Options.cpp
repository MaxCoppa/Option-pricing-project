//
//  Options.cpp
//  Pricing Options
//
//  Created by Marama on 29/12/2023.
//

#include "Options.hpp"

// Default constructor initializes option with default values
Option::Option() : type(1), r(0.0473), K(220), T(1), sigma(0.126299), S0(200) {}

// Parameterized constructor to set option parameters
Option::Option(int type0, double r0, double K0, double T0, double sigma0, double S)
{type = type0; r = r0; K = K0; T = T0; sigma = sigma0; S0 = S;};

// Getter methods
int Option::Get_type() const
{
    return type;
}

double Option::Get_risk_free_rate() const
{
    return r;
}

double Option::Get_strike_price() const
{
    return K;
}

double Option::Get_expiry_date() const
{
    return T;
}

double Option::Get_volatility() const
{
    return sigma;
}

double Option::Get_initial_price() const
{
    return S0;
}

// Setter methods
void Option::Set_type(bool b)
{
    type = b;
}

void Option::Set_risk_free_rate(double r0)
{
    r = r0;
}

void Option::Set_strike_price(double K0)
{
    K = K0;
}

void Option::Set_expiry_date(double T0)
{
    T = T0;
}

void Option::Set_initial_price(double S)
{
    S0 = S;
}

// Output method to display option information
void Option::output() const
{
    if (type) {
        std::cout << "This is a call option." << std::endl;
    }
    else {
        std::cout << "This is a put option." << std::endl;
    }
    std::cout << "The zero coupon risk-free rate: " << r << std::endl;
    std::cout << "The Strike price of the Option: " << K << std::endl;
    std::cout << "The Expiry date of the Option: " << T << std::endl;
    std::cout << "The Volatility of the underlying asset: " << sigma << std::endl;
    std::cout << "The initial price of the underlying asset: " << S0 << std::endl;
}
