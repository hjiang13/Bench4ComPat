#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Function to generate a random number from a standard normal distribution
double random_normal() {
    static int hasSpare = 0;
    static double spare;
    if (hasSpare) {
        hasSpare = 0;
        return spare;
    }

    hasSpare = 1;
    double u, v, s;
    do {
        u = (rand() / ((double) RAND_MAX)) * 2.0 - 1.0;
        v = (rand() / ((double) RAND_MAX)) * 2.0 - 1.0;
        s = u * u + v * v;
    } while (s >= 1.0 || s == 0.0);

    s = sqrt(-2.0 * log(s) / s);
    spare = v * s;
    return u * s;
}

// Function to estimate the price of a European call option using Monte Carlo simulation
double monte_carlo_call_price(int num_samples, double S, double K, double r, double sigma, double T) {
    double sum_payoff = 0.0;

    for (int i = 0; i < num_samples; i++) {
        double Z = random_normal();
        double ST = S * exp((r - 0.5 * sigma * sigma) * T + sigma * sqrt(T) * Z);
        double payoff = fmax(ST - K, 0.0);
        sum_payoff += payoff;
    }

    double mean_payoff = sum_payoff / num_samples;
    return exp(-r * T) * mean_payoff;
}

int main() {
    int num_samples = 1000000;  // Number of Monte Carlo samples
    double S = 100.0;  // Initial stock price
    double K = 100.0;  // Strike price
    double r = 0.05;  // Risk-free interest rate
    double sigma = 0.2;  // Volatility
    double T = 1.0;  // Time to maturity in years

    srand(time(NULL));

    double call_price = monte_carlo_call_price(num_samples, S, K, r, sigma, T);
    printf("Estimated European call option price: %f\n", call_price);

    return 0;
}
