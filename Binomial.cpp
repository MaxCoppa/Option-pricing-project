//
//  Binomial.cpp
//  Pricing Options
//
//  Created by Marama on 29/12/2023.
//

#include "Binomial.hpp"
#include "Options.hpp"

#include <cmath>  // For functions like exp
#include <algorithm> // For function like max

using namespace std;

// Constructors and destructor
// Default constructor
European_Option_Binomial::European_Option_Binomial() : PV(0), p(0.5), fu(0), fd(0),  u(0), d(0) {}

European_Option_Binomial::European_Option_Binomial(double PV0, double p0, double fu0,  double fd0, double u0,  double d0)
{ PV = PV0;  p = p0;  fu = fu0;   fd = fd0;  u = u0;   d = d0;};



// Getter methods
double European_Option_Binomial::Get_magnitude_of_an_upjump() const  // Get the magnitude of an up-jump
{
    return u;
};

double European_Option_Binomial::Get_magnitude_of_an_downjump() const   // Get the magnitude of an down-jump
{
    return d;
};

double European_Option_Binomial::Get_probability_of_an_upjump() const    // Get the probability of an up-jump
{
    return p;
};

double European_Option_Binomial::Get_option_value_at_u() const    // Get the option value at u
{
    return fu;
};

double European_Option_Binomial::Get_option_value_at_d() const    // Get the option value at d
{
    return fd;
};

double European_Option_Binomial::Get_the_current_value_of_the_option() const   // Get the current value of the option
{
    return PV;
};




// Setter methods
void European_Option_Binomial::Set_Magnitude(double sigma0, double T)
{
    u = exp(sigma0 * sqrt(T));
    d = 1/u; // We have the formula u*d = 1

};
void European_Option_Binomial::Set_probability_of_an_upjump(double r0, double T0, double u0, double d0)
{
    p = (exp(r0 * T0) - d0)/(u0 - d0);
};


void European_Option_Binomial::Set_call_option_value_at_time_T(double K0, double S0, double u0, double d0, double r0)
{
    const double a((u0 * S0) - K0) ;
    const double c = 0;
    const double b = (d0 * S0) - K0;
    fu = max(a, c);
    fd = max(b, c);
    PV = ((p * fu) + (1 - p)*fd)/(1+r0);
};


void European_Option_Binomial::Set_put_option_value_at_time_T(double K0, double S0, double u0, double d0, double r0)
{
    const double a(K0 - (u0 * S0)) ;
    const double c = 0;
    const double b = K0 - (d0 * S0);
    fu = max(a, c);
    fd = max(b, c);
    PV = ((p * fu) + (1 - p)*fd)/(1+r0);
};



// Binomial method for option pricing
double European_Option_Binomial::Binomial_Method_Price_option_one_step(Option O)
{
    double r = O.Get_risk_free_rate();
    double K = O.Get_strike_price();
    double T = O.Get_expiry_date();
    double sigma = O.Get_volatility();
    double S0 = O.Get_initial_price();
    int type0 = O.Get_type();
    
    European_Option_Binomial B = European_Option_Binomial();
    
    if(type0 == 1) {
        B.Set_Magnitude(sigma, T);

        B.Set_probability_of_an_upjump(r, T, B.Get_magnitude_of_an_upjump(), B.Get_magnitude_of_an_downjump());

        B.Set_call_option_value_at_time_T(K,S0,B.Get_magnitude_of_an_upjump(), B.Get_magnitude_of_an_downjump(), r);
    }
    else {
        B.Set_Magnitude(sigma, T);

        B.Set_probability_of_an_upjump(r, T, B.Get_magnitude_of_an_upjump(), B.Get_magnitude_of_an_downjump());

        B.Set_put_option_value_at_time_T(K,S0,B.Get_magnitude_of_an_upjump(), B.Get_magnitude_of_an_downjump(), r);
        std::cout << "The value of fu is " << B.Get_option_value_at_u()<< std::endl;
        std::cout << "The value of fd is " << B.Get_option_value_at_d()<< std::endl;
    }

    cout << "The price of the option with a one step Binomial method is :" << endl;

    return B.Get_the_current_value_of_the_option();
    
};


// Binomial method for option pricing with steps
double European_Option_Binomial::Binomial_Method_Price_option_steps(Option O, int n) // n is the number of steps in the tree
{
    if (n<=0) {
        cout << "Not possible n <= 0" << endl;
        return 0;
        
    } else {
        
        double r = O.Get_risk_free_rate();
        double K = O.Get_strike_price();
        double T = O.Get_expiry_date();
        double sigma = O.Get_volatility();
        double S0 = O.Get_initial_price();
        int type0 = O.Get_type();
        double deltaT = T/n;
        
                
        double u0 = exp(sigma * sqrt(deltaT));
        double d0 = 1/u0;
        

        double p = (exp(r * deltaT) - d0)/(u0 - d0);
        double q = 1 - p;
        
        

        double valueoff[n+1];
        
        
        if(type0 == 1) {
            
            for (int i = 0; i < n+1; ++i) {
                valueoff[i] = S0 * pow(u0, (n - i)) * pow((d0), (i)) - K;
                if (valueoff[i] < 0) valueoff[i] = 0;
            }
            
            
            // loop to compute the price of the option
            for (int j = n; j>= 0; --j) {
                for (int i = 0; i < j; ++i) {
                    valueoff[i] = p * valueoff[i] + q * valueoff[i + 1];
                }
            }
        }
        else {
            // loop that computes every fuu... and fdd...
            for (int i = 0; i < n+1; ++i) {
                valueoff[i] = K -(S0 * pow((u0), (n - i)) * pow((d0), (i)));
                if (valueoff[i] < 0) valueoff[i] = 0;
            }
            
            
            // loop to compute the price of the option
            for (int j = n; j>= 0; --j) {
                for (int i = 0; i < j; ++i) {
                    valueoff[i] = p * valueoff[i] + q * valueoff[i + 1];
                }
            }
        }
        
        double P = valueoff[0];
        
        P = P * exp(-(r * T));
        
        return P;
    }
}
//

