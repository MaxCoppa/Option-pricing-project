//
//  Binomial.hpp
//  Pricing Options
//
//  Created by Marama on 29/12/2023.
//


#pragma once

#include <stdio.h>
#include "Options.hpp"


// On se place dans le cas d'une European Option
class European_Option_Binomial
{
    public:
    // Constructors and destructor
    European_Option_Binomial();   // Default constructor
    European_Option_Binomial(double PV, double p, double fu,  double fd, double u,  double d);   // Parameterized constructor
    ~European_Option_Binomial () {}   // Destructor


    // Getter methods
    double Get_magnitude_of_an_upjump() const;   // Get the magnitude of an up-jump
    double Get_magnitude_of_an_downjump() const;   // Get the magnitude of an down-jump
    double Get_probability_of_an_upjump() const;   // Get the probability of an up-jump
    double Get_option_value_at_u() const;   // Get the option value at u
    double Get_option_value_at_d() const;   // Get the option value at d
    double Get_the_current_value_of_the_option() const;   // Get the current value of the option


    // Setter methods
    void Set_Magnitude(double, double);   // Set the magnitude of an up-jump and a down-jump
    void Set_probability_of_an_upjump(double, double, double, double);   // Set the probability of an up-jump
    void Set_call_option_value_at_time_T(double, double, double, double, double);   // Set the call option value at time T
    void Set_put_option_value_at_time_T(double, double, double, double, double);   // Set the put option value at time T
    
    
    // Binomial method for option pricing with one step
    double Binomial_Method_Price_option_one_step(Option);

    
    // Binomial method for option pricing with steps
    double Binomial_Method_Price_option_steps(Option, int);


    
    private:
    // Attributs
    
    double PV; // current value (t=0) of the option
    double p; // probability of an up-jump
    double fu; // option value at u
    double fd; // option value at d
    double u; // the magnitude of an up-jump
    double d; // the magnitute of a down-jump
    
};


// #endif /* Binomial_hpp */
