//
//  Monte_carlo.hpp
//  Pricing Options
//
//  Created by Marama on 29/12/2023.
//

#pragma once

#include <iostream>
#include "Options.hpp"

class Monte_Carlo_Simulation {

private:
    int N;  // Number of simulations
    int n;  // Number of divisions for the time of the option
    int N_visualization; // Number of simulations for the visualization

public:
    // Constructors and destructor
    Monte_Carlo_Simulation();   // Default constructor
    Monte_Carlo_Simulation(int N, int n, int N_visualization);   // Parameterized constructor


    // Getter methods
    int Get_number_of_simulation() const;   // Get the number of simulations
    int Get_number_of_divisions() const;   // Get the number of divisions
    int Get_number_of_visualization() const; // Get the number of simulations for the visualization

    // Setter methods
    void Set_number_of_simulation(int);   // Set the number of simulations
    void Set_number_of_divisions(int);   // Set the number of divisions
    void Set_number_of_visualization(int); // Set the number of simulations for the visualization

    // Output method to display simulation information
    void output() const;

    // Method to generate a random number
    double random_number();

    // Method to perform Monte Carlo simulation for option pricing
    double Monte_Carlo_Simulation_Price(Option);
    double Monte_Carlo_Simulation_Visualization(Option);
};
