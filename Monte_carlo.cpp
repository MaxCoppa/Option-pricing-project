//
//  Monte_carlo.cpp
//  Pricing Options
//
//  Created by Marama on 29/12/2023.
//

#include "Monte_Carlo.hpp"
#include "Options.hpp"
#include <random>

// Default constructor initializes simulation with default values
Monte_Carlo_Simulation::Monte_Carlo_Simulation()
{N = 10000; n = 1000; N_visualization = 100;};

// Parameterized constructor to set simulation parameters
Monte_Carlo_Simulation::Monte_Carlo_Simulation(int N0, int n0, int N00)
{N = N0; n = n0; N_visualization = N00;};

// Getter methods
int Monte_Carlo_Simulation::Get_number_of_simulation() const
{
    return N;
}

int Monte_Carlo_Simulation::Get_number_of_divisions() const
{
    return n;
}

int Monte_Carlo_Simulation::Get_number_of_visualization() const
{
    return N_visualization;
}

// Setter methods
void Monte_Carlo_Simulation::Set_number_of_simulation(int N0)
{
    N = N0;
}

void Monte_Carlo_Simulation::Set_number_of_divisions(int n0)
{
    n = n0;
}

void Monte_Carlo_Simulation::Set_number_of_visualization(int N00)
{
    N_visualization = N00;
}

// Output method to display simulation information
void Monte_Carlo_Simulation::output() const
{
    std::cout << "The number of Simulations in this Monte Carlo simulation: " << N << std::endl;
    std::cout << "The number of Divisions of time in this Monte Carlo simulation: " << n << std::endl;
    std::cout << "The number of Simulations for the visualization of this Monte Carlo simulation: " << N_visualization << std::endl;
}

// Method to generate a random number using a normal distribution
double Monte_Carlo_Simulation::random_number()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> distribution(0.0, 1.0);

    return distribution(gen);
}

// Method to perform Monte Carlo simulation for option pricing
double Monte_Carlo_Simulation::Monte_Carlo_Simulation_Price(Option o)
{
    int type = o.Get_type();
    double r = o.Get_risk_free_rate();
    double K = o.Get_strike_price();
    double T = o.Get_expiry_date();
    double sigma = o.Get_volatility();
    double S0 = o.Get_initial_price();

    double S;
    double Payoff;
    double Z;

    double t = T/n ;
    double sqrtt = sqrt(t);
    double actualisation = exp(-r*T);

    double ret = 0.0;
    for (int i = 0; i < N; ++i) {
        S = S0;
        for (int j = 1; j < n; ++j) {
            Z = random_number();
            // Update the asset price using the Black-Scholes model
            S = S * exp((r - 0.5 * sigma * sigma) * t + sigma * sqrtt * Z);
        }
        // Calculate the payoff of the option
        Payoff = type * (S - K);
        // Accumulate the discounted payoff
        if (Payoff > 0.0){
            ret += actualisation * Payoff;
        }
    }

    // Calculate the average payoff over all simulations
    ret = ret/N;

    return ret;
}


// Method to perform Monte Carlo simulation for option pricing
double Monte_Carlo_Simulation::Monte_Carlo_Simulation_Visualization(Option o)
{
    int type = o.Get_type();
    double r = o.Get_risk_free_rate();
    double K = o.Get_strike_price();
    double T = o.Get_expiry_date();
    double sigma = o.Get_volatility();
    double S0 = o.Get_initial_price();

    double S;
    double Payoff;
    double Z;

    double t = T/n ;
    double sqrtt = sqrt(t);
    double actualisation = exp(-r*T);

    double ret = 0.0;

    // Use GNU Plot to plot the values of S over time
    FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
    if (!gnuplotPipe) {
        std::cerr << "Error opening pipe to GNU Plot." << std::endl;
        return 0.0 ;
    }

    // Create a GNU Plot script to plot the values of S over time
    fprintf(gnuplotPipe, "set title 'Underlying Asset Evolution Simulation'\n");
    fprintf(gnuplotPipe, "set xlabel 'Time (years)'\n");
    fprintf(gnuplotPipe, "set ylabel 'Underlying Asset Value'\n");
    fprintf(gnuplotPipe, "plot ");

    for (int i = 1; i <= 100; ++i) {
        fprintf(gnuplotPipe, "'-' with lines title ''");
        if (i < 100) {
            fprintf(gnuplotPipe, ", ");
        }
    }
    fprintf(gnuplotPipe, "\n");

    for (int i = 0; i < N_visualization; ++i) {
        S = S0;

        for (int j = 1; j < n; ++j) {
            fprintf(gnuplotPipe, "%f %f\n", j * t, S);

            Z = random_number();
            // Update the asset price using the Black-Scholes model
            S = S * exp((r - 0.5 * sigma * sigma) * t + sigma * sqrtt * Z);
        }
        fprintf(gnuplotPipe, "e\n");

        // Calculate the payoff of the option
        Payoff = type * (S - K);
        // Accumulate the discounted payoff
        if (Payoff > 0.0){
            ret += actualisation * Payoff;


        }
    }

    // Close the pipe
    pclose(gnuplotPipe);


    // Calculate the average payoff over all simulations
    ret = ret/N_visualization;

    return ret;
}
