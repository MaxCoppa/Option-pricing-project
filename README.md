# Option pricing

Option pricing have been a topic of interest for many years in the financial industry. There are
several option pricing methods, including Binomial trees and Monte-Carlo simulations. The first
one has been introduced in 1979 by Cox, Ross and Rubinstein while the second one was applied
first in 1977 by Phelim Boyle.
In this project, we have implemented both option pricing methods. The simulation allows
users to calculate the price of an option knowing the current price of the underlying asset, the
strike price and the time to maturity. The simulation was implemented using computer science
principles and algorithms, including data structures and mathematical models.

# How to run the project 

Our project contains several files, including a main file. The idea was to separate the files to
make them clearer.

So we have the following files :

- main.cpp file containing the main code, our test functions and the main function
- Option.cpp and Option.hpp files for creating our Option class
- Binomial.cpp and Binomial.hpp files for creating our Binomial class and applying the
Binomial method
- Monte_Carlo.cpp and Monte_Carlo.hpp files to create our Monte-Carlo class and formalise
the Monte-Carlo method in code
-  Volatility_estimator.cpp and Volatility_estimator.hpp files to estimate the volatility
of our underlying asset

In the main.cpp, we created two test functions test1 and test2. They are void functions
that return the price of the option with the Binomial Method and also with the Monte-Carlo
Method. It allows us to compare the results that we find with the two methods.
Here is a more detailed explanation :
- test1() gives the price of a call option, with Apple being the underlying asset, with both
the Binomial Method and the Monte-Carlo Method
- test2() gives the price of a put option, with Apple being the underlying asset, with both
the Binomial Method and the Monte-Carlo Method

One could try one function at a time to see that our code works.

It is also possible to carry out tests quite easily. All you have to do is decide on which underlying
asset the option is to be implemented. Then all we have to do is change the parameters
we want (maturity, risk free rate, etc.) in relation to the option we want to price. All that’s left
to do is run our code and see the prices returned by the two methods.

We also implemented a visualization method Monte_Carlo_Simulation_Visualization(Option)
for the underlying asset of the option simulates thanks to the Monte-Carlo Method. It requires
you to have GnuPlot installed on your software and then run the code.
3
